from setuptools import setup, Extension

setup(
    name='symNMF',
    version='1.0',
    description="A sample C-API",



    classifiers=[
        'Developments status :: 3 - Alpha',
        'License :: OSI Approved :: GNU General Public License v2 (GPLv2)',
        'Natural Language:: English',
        'Programing Language :: Python :: 3 :: Only',
        'Programming Language :: Python :: Implementation :: CPython',
    ],
    ext_modules=[
        Extension(
            'symNMF',
            ['symnmf.c','symnmfmodule.c'],
        ),
    ]
)