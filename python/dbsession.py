# coding: utf-8

from contextlib import contextmanager
from sqlalchemy import create_engine, MetaData, Table
from sqlalchemy.orm import sessionmaker, scoped_session
from sqlalchemy.ext.declarative import declarative_base


SQLALCHEMY_DATABASE_URI = ''


__all__ = ['db', 'AdminRoles', 'AdminUser']

engine = create_engine(SQLALCHEMY_DATABASE_URI, pool_size=5, pool_recycle=300, max_overflow=3, echo=True)
metadata = MetaData(bind=engine)

session_factory = sessionmaker(bind=engine)

class Session(object):
    def __init__(self, cls=session_factory):
        self.session = scoped_session(cls)

    @contextmanager
    def auto_commit(self, throw=True):
        try:
            yield
            self.session.commit()
        except Exception as e:
            self.session.rollback()
            if throw:
                raise e

    def __del__(self):
        self.close()

    def close(self):
        self.session.remove()

db = Session()

Base = declarative_base()