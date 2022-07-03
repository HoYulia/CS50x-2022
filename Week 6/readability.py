from cs50 import get_string
import re
import math

text = get_string("Text: ")

# Calculate letters, words, sentences
letters = len(re.findall("[a-zA-Z]", text))
words = len(re.findall("\s", text)) + 1
sentences = len([i for i in text if i in ".!?"])

# Calculate index
l = letters / words * 100
s = sentences / words * 100
index = round(0.0588 * l - 0.296 * s - 15.8)

# Output Grade
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")