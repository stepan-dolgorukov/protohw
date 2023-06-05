from os import environ


def access_token():
    environment_variable_token = "VK_API_ACCESS_TOKEN"
    token = environ.get(environment_variable_token)

    if token is None:
        raise EnvironmentError(
            f"В окружении отсутствует переменная {environment_variable_token}.")

    return token
