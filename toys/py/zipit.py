#!/usr/bin/env python
import os
import zipfile

# http://stackoverflow.com/questions/1855095/how-to-create-a-zip-archive-of-a-directory

def zipdir(path, ziph):
    # ziph is zipfile handle
    for root, dirs, files in os.walk(path):
        for file in files:
            ziph.write(os.path.join(root, file))

if __name__ == '__main__':

# PR_1376
# PR_3576
# PR_3818
# PR_3829
# PR_4045
# PR_4046

    zipf = zipfile.ZipFile('PR_1376.zip', 'w', zipfile.ZIP_DEFLATED)
    zipdir('PR_1376/', zipf)
    zipf.close()

    zipf = zipfile.ZipFile('PR_3576.zip', 'w', zipfile.ZIP_DEFLATED)
    zipdir('PR_3576/', zipf)
    zipf.close()

    zipf = zipfile.ZipFile('PR_3818.zip', 'w', zipfile.ZIP_DEFLATED)
    zipdir('PR_3818/', zipf)
    zipf.close()

    zipf = zipfile.ZipFile('PR_3829.zip', 'w', zipfile.ZIP_DEFLATED)
    zipdir('PR_3829/', zipf)
    zipf.close()

    zipf = zipfile.ZipFile('PR_4045.zip', 'w', zipfile.ZIP_DEFLATED)
    zipdir('PR_4045/', zipf)
    zipf.close()

    zipf = zipfile.ZipFile('PR_4046.zip', 'w', zipfile.ZIP_DEFLATED)
    zipdir('PR_4046/', zipf)
    zipf.close()


