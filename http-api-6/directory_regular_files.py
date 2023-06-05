from os import listdir

def directory_regular_files(dir_name: str):
    regular_files = set()

    for file in listdir(dir_name):
        # THINK
        regular_files.add(file)

    return regular_files