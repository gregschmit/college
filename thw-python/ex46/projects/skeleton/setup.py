try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

config = {
    'description': 'My Project',
    'author': 'Gregory N. Schmit',
    'url': 'http://test.dev/',
    'download_url': 'http://test.dev/download/',
    'author_email': 'schmitgreg@outlook.com',
    'version': '0.1',
    'install_requires': ['nose'],
    'packages': ['NAME'],
    'scripts': [],
    'name': 'projectname'
}

setup(**config)
