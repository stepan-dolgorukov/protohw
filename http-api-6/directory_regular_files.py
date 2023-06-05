from os import listdir
from pathlib import Path
import magic

def directory_regular_files(directory: Path):
    regular_files = set()
    types_images = {"png", "jpeg"}

    for file in listdir(directory):
        type_file = magic.from_file(directory / file).lower()

        for type_img in types_images:
            if type_file.startswith(type_img):
                regular_files.add(file)
                break

    return regular_files