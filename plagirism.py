import difflib
import random

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
`#include<stdio.h>
int main() {
    int i;
    for(i = 0; i < 10; i++) {
        printf("%d ", i);
    }
    return 0;
}
"""

# Input C code from the user (as a string)
input_c_code = """
#include<stdio.h>
int main() {
    int count;
    for(count = 0; count < 10; count++) {
        printf("%d ", count);
    }
    return 0;
}
"""

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
