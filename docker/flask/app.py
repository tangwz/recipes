# coding: utf-8

from flask import Flask
from redis import Redis
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
redis = Redis(host='redis', port=6379)

app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://flask:flask@localhost/flask'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True)

    def __init__(self, username):
        self.username = username

    def __repr__(self):
        return '<User %r>' % self.username

@app.route('/')
def hello():
    guest = User('guest')
    db.session.add(guest)
    db.commit()
    guest = User.query.filter_by(username='guest').first()

    redis.incr('hits')
    return 'Hello %s! I have been seen %s times.' % guest, redis.get('hits')


if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)