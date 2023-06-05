#!/usr/bin/env python3

import vk
import requests
from argparse import ArgumentParser

from directory_regular_files import directory_regular_files
from access_token import access_token

if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument('-a', '--aid', help='Идентификатор альбома')
    parser.add_argument('-d', '--dir', help='Каталог с файлами на загрузку')

    args = parser.parse_args()

    if args.aid is None:
        print("Не задан идентификатор альбома.")
        exit(1)

    if args.dir is None:
        print("Не задан каталог с файлами на загрузку.")
        exit(1)

    token = None
    api = None
    server = None
    server_url = None

    try:
        token = access_token()
    except EnvironmentError as env_err:
        print(env_err)
        exit(1)

    try:
        api = vk.API(access_token=token, v="5.131")
    except Exception as err:
        print(err)
        exit(1)

    try:
        server = api.photos.getUploadServer(album_id=args.aid)
    except Exception as err:
        print(err)
        exit(1)

    try:
        server_url = server["upload_url"]
    except Exception as err:
        print(err)
        exit(1)

    for file in directory_regular_files(args.dir):
        print(f"Загружается {file}")
        path_file = args.dir + '/' + file

        try:
            responce = requests.post(server_url, files={"file1": open(path_file, "rb")})
            json_responce = responce.json()

            api.photos.save(
                album_id=json_responce["aid"],
                server=json_responce["server"],
                photos_list=json_responce["photos_list"],
                hash=json_responce["hash"])
        except Exception as err:
            print(f"Не удалось загрузить файл {file}")
            print(err)
            continue