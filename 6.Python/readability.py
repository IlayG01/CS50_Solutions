def luhn_formula(letters, words, sentences):
    return (0.0588 * (100/words*letters)) - (0.296 * (100/words*sentences)) - 15.8


def output(index):
    if index < 1:
        print("Before Grade 1\n")
    if index > 16:
        print("Grade 16+\n")
    else:
        print(f"Grade {index}\n")


def main():
    text = input("Enter your text -- > ")
    # check for content vetween space / / ? !
    letters_between_words = 0
    # counters
    letters_counter = 0
    words_counter = 0
    sentences_counter = 0

    for char in text:
        # a-z A-Z
        if(ord(char.upper()) >= 65 and ord(char.upper()) <= 90):
            letters_counter += 1
            letters_between_words += 1
        # space
        if(ord(char) == 32):
            if(letters_between_words >= 1):
                words_counter += 1
                letters_between_words = 0
        # ? ! .
        if(ord(char) in [46, 33, 63]):
            if (letters_between_words >= 1):
                sentences_counter += 1
                words_counter += 1
                letters_between_words = 0
    output(round(luhn_formula(letters_counter, words_counter, sentences_counter)))


main()