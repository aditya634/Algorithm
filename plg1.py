import difflib
import sys

# Helper function to compare two strings for similarity (using SequenceMatcher)


def get_similarity(code1, code2):
    matcher = difflib.SequenceMatcher(None, code1, code2)
    return matcher.ratio() * 100  # Return percentage of similarity

# Function to modify code by renaming variables or changing structure without altering functionality


def modify_code(c_code):
    lines = c_code.split("\n")
    modified_lines = []

    for line in lines:
        # Example modifications: Renaming variables and function names
        if 'int' in line or 'float' in line:
            line = line.replace('int', 'long').replace('float', 'double')

        # Another example: Modify loop conditions slightly
        if 'for' in line or 'while' in line:
            if '++' in line:
                # Switch increment to decrement
                line = line.replace('++', '--')

        modified_lines.append(line)

    return "\n".join(modified_lines)


# Sample known C code to compare against (normally you'd have a database of multiple known codes)
known_c_code = """
#include<stdio.h>
int main() {
    int i;
    for(i = 0; i < 10; i++) {
        printf("%d ", i);
    }
    return 0;
}
"""

# Function to read C code from terminal input


def read_code_from_terminal():
    print("Enter the C code (end input with an empty line):")
    input_lines = []
    while True:
        line = sys.stdin.readline()
        if line.strip() == "":
            break
        input_lines.append(line)

    return ''.join(input_lines)


# Read C code from terminal
input_c_code = read_code_from_terminal()

# Check plagiarism (using similarity ratio)
similarity_percentage = get_similarity(input_c_code, known_c_code)
print(f"Plagiarism Percentage: {similarity_percentage:.2f}%")


# If plagiarism is above 50%, modify the code
if similarity_percentage > 50:
    print("Plagiarism detected! Modifying code...")
    modified_code = modify_code(input_c_code)
    print("Modified Code:\n")
    print(modified_code)
else:
    print("No significant plagiarism detected.")
