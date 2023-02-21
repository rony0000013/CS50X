# TODO
import re

text = input("Text: ")
sentences = len(re.findall(r'[\.?!]', text))    # count sentences
words = len(re.findall(r' ', text)) + 1     # count words
letters = len(re.findall(r'\w', text))     # count leters


index = round(0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 15:
    print("Grade 16+")
else:
    print(f"Grade {index}")