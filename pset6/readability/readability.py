import cs50

def main():

    # get user input
    text = cs50.get_string("Text: ")

    # count number of letters
    letters = 0
    for i in text:
        if i.isalpha():
            letters += 1

    # count number of words
    words = len(text.split())

    # count sentences - work on assumption all sentences end with one of . ! ?
    sentences = 0
    for i in text:
        if i in [".", "!", "?"]:
            sentences += 1

    # calculate formula - index = 0.0588 * L - 0.296 * S - 15.8 where L is the average number of letters per 100 words, S is the average number of sentences per 100 words
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # output
    if index >= 16:
        print(f"Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")

# Run program
main()