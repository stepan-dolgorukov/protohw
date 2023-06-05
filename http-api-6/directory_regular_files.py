from os import listdir
from pathlib import Path

def directory_regular_files(directory: Path):
    regular_files = set()

    for file in listdir(directory):
        regular_files.add(file)

    return regular_files