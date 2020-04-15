#!/usr/bin/env python3

from setuptools import setup, find_packages

def main():
    print('hello')
    return


if __name__ == "__main__":
    setup(name='omgpython',
          version='0.2',
          description='oh my gosh Python!',
          author="The Dude",
          maintainer="The Dudette",
          maintainer_email='the_dude@gmail.com',
          url='https://github.com/the_dude/omgpython',
          platforms='any',
          license="OMGPL 3.14",
          long_description="An interesting collection of subtle & tricky Python Snippets"
                           " and features.",
          keywords="omgpython gotchas snippets tricky",
          packages=find_packages(),
          entry_points = {
              'console_scripts': ['omgpython = omg_python.main:load_and_read']
          },
          classifiers=[
              'Development Status :: 4 - Beta',

              'Environment :: Console',
              'Environment :: MacOS X',
              'Environment :: Win32 (MS Windows)',

              'Intended Audience :: Science/Research',
              'Intended Audience :: Developers',
              'Intended Audience :: Education',
              'Intended Audience :: End Users/Desktop',

              'Operating System :: OS Independent',

              'Programming Language :: Python :: 3',
              'Programming Language :: Python :: 2',

              'Topic :: Documentation',
              'Topic :: Education',
              'Topic :: Scientific/Engineering',
              'Topic :: Software Development'],
            )

