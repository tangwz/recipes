# coding: utf-8

from werkzeug.wrappers import Request, Response
from werkzeug._internal import _easteregg

@Request.application
def app(request):
    return Response('Hello World')

if __name__ == '__main__':
    from werkzeug.serving import run_simple
    run_simple('', 5000, _easteregg(app))