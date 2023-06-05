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
    token = None

    try:
        token = access_token()
    except EnvironmentError as env_err:
        print(env_err)
        exit(1)

    api = vk.API(access_token=token, v="5.131")
    server = api.photos.getUploadServer(album_id=args.aid)
    server_url = server["upload_url"]

    for file in directory_regular_files(args.dir):
        print(f"Загружается {file}")
        path_file = args.dir + '/' + file

        responce = requests.post(server_url, files={"file1": open(path_file, "rb")})
        json_responce = responce.json()

        api.photos.save(
            album_id=json_responce["aid"],
            server=json_responce["server"],
            photos_list=json_responce["photos_list"],
            hash=json_responce["hash"])