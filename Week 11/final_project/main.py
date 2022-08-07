from flask import Flask, render_template, redirect, url_for, request
from flask_bootstrap import Bootstrap
from flask_sqlalchemy import SQLAlchemy
from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField, FloatField
from wtforms.validators import DataRequired
import requests

app = Flask(__name__)
app.config['SECRET_KEY'] = '8BYkEfBA6O6donzWlSihBXox7C0sKR6b'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///movie-database.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)
Bootstrap(app)

movie_api_key = "6393e3b2108d57c3b7fe5b2d1e8119ce"
end_point = "https://api.themoviedb.org/3/search/movie?"
movie_api_read_access_token = "eyJhbGciOiJIUzI1NiJ9.eyJhdWQiOiI2MzkzZTNiMjEwOGQ1N2MzYjdmZTViMmQxZTgxMTljZSIsInN1YiI6" \
                              "IjYwNjJhNjExOGYyNmJjMDA3NzZjM2Q4MiIsInNjb3BlcyI6WyJhcGlfcmVhZCJdLCJ2ZXJzaW9uIjoxfQ.XCc6" \
                              "IgdCMI4crgp43hAxsnHG23PgMpmiFp23HGebM5I"
movie_list = []


class EditForm(FlaskForm):
    rating = FloatField("Your rating out of 10 eg 7.5", validators=[DataRequired()])
    review = StringField("Your review", validators=[DataRequired()])
    submit = SubmitField("Done")


class AddMovie(FlaskForm):
    title = StringField("Movie Title", validators=[DataRequired()])
    submit = SubmitField("Add Movie")


class Movie(db.Model):
    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    title = db.Column(db.String(550), nullable=False)
    year = db.Column(db.String(250), nullable=False)
    description = db.Column(db.String(550), nullable=False)
    rating = db.Column(db.Float(5), nullable=True)
    ranking = db.Column(db.Integer, nullable=True)
    review = db.Column(db.String(500), nullable=True)
    img_url = db.Column(db.String(400), nullable=False)


db.create_all()


@app.route("/")
def home():
    global movie_list
    all_movies = db.session.query(Movie).order_by("rating").all()
    n = 1
    for movie in reversed(all_movies):
        movie.ranking = n
        n += 1
    db.session.commit()

    movie_list = []
    return render_template("index.html", list_of_movies=all_movies)


@app.route("/edit", methods=["GET", "POST"])
def update():
    url_id = request.args.get("id")
    form = EditForm()
    if form.validate_on_submit():
        movie_to_eit = Movie.query.get(url_id)
        movie_to_eit.rating = request.values.get("rating")
        movie_to_eit.review = request.values.get("review")
        db.session.commit()

        return redirect("/")
    elif url_id is not None:
        return render_template("edit.html", form=form, url_id=url_id)
    else:
        return redirect("/")


@app.route("/delete/<int:url_id>")
def delete(url_id):
    movie_to_delete = Movie.query.get(url_id)
    db.session.delete(movie_to_delete)
    db.session.commit()
    return redirect("/")


@app.route("/add", methods=["POST", "GET"])
def add_movies():
    form = AddMovie()
    movie_id = request.args.get("movie_id")
    if request.method == "POST" and form.validate_on_submit():
        params = {
            "api_key": movie_api_key,
            "query": request.values.get("title"),
            "page": 1,
            "include_adult": False,
        }
        response = requests.get(url=end_point, params=params)
        movie_list.append(response.json())
        return render_template("select.html", selections=response.json()["results"])
    if movie_id is not None:
        for x in movie_list[0]["results"]:
            if int(x["id"]) == int(movie_id):
                new_movie = Movie(
                    title=x["original_title"],
                    img_url=f'https://image.tmdb.org/t/p/original{x["poster_path"]}',
                    year=x["release_date"],
                    rating=5,
                    ranking=5,
                    review="Piece of shit",
                    description=x["overview"]
                )
                db.session.add(new_movie)
                db.session.commit()
                edit_movie_rating = Movie.query.filter_by(title=x["original_title"]).first()
                url_id = edit_movie_rating.id
                return redirect(f"/edit?id={url_id}")

    return render_template("add.html", form=form)


if __name__ == '__main__':
    app.run(debug=True)