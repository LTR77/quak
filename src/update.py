from urllib.request import urlretrieve
import requests
import zipfile
import hashlib
import shutil
import sys
import os

def CheckLocalHash(file):
    BUF_SIZE = 65536
    print("Checking for Updates!")
    sha256 = hashlib.sha256()
    with open("version.txt", "rb") as f:
        print("Reading Local Hash from version.txt..")
        data = f.read(BUF_SIZE)
        sha256.update(data)
    print("Got Hash!")
    return sha256.hexdigest()
def CheckGHHash():
    sha256 = hashlib.sha256()
    print("Reading Github FIle..")
    url = "https://raw.githubusercontent.com/LTR77/quak/main/version.txt"
    response = requests.get(url)
    sha256.update(response.content)
    print("Got Hash!")
    return sha256.hexdigest()

local_file_hash = CheckLocalHash(sys.argv[0])
github_file_hash = CheckGHHash()
print(f"Local File Hash = {local_file_hash}")
print(f"Github File Hash = {github_file_hash}")
print("Comparing Hashes...")
if local_file_hash == github_file_hash:
    print("Hashes Match, No Update needed!")
else:
    print("Hashes do not Match")
    game_update_wanted = input("Do you want to update the Game? y/n : ")
    if game_update_wanted == "y":
        print("Updating..")
        url = "https://github.com/LTR77/quak/archive/refs/heads/main.zip"
        filename = "upd.zip"
        print("Installing Upgrade..")
        print("Downloading.. (1/4)")
        urlretrieve(url, filename)
        print("Finished Downloading Files!")
        print("Extracting.. (2/4)")
        if os.path.exists("temp"):
            shutil.rmtree("temp")
        else:
            os.mkdir("temp")
        zip = zipfile.ZipFile(filename, "r")
        zip.extractall(path="temp")
        zip.close()
        print("Finished Extracting!")
        print("Updating Files.. (3/4)")
        with open("version.txt", "w") as src_version, open("temp/quak-main/src/version.txt", "r") as dest_version:
            src_version.write(dest_version.read())
            print("Wrote to version.txt")
        with open("main.cpp", "w") as src_game, open("temp/quak-main/src/main.cpp", "r") as dest_game:
            src_game.write(dest_game.read())
            print("Wrote to main.cpp")
        path = os.path.join("..", "resources")
        try:
            if os.path.exists(path):
                shutil.rmtree(path)
            print("Deleted resources directory for Replacement!")
            shutil.copytree("temp/quak-main/resources", path)
            print("Wrote to ../resources/*")
        except FileExistsError:
            print("Failed to Replace ../resources: File Already Exists")
        except PermissionError:
            print("Failed to Replace ../resources: Permission Error")
        except FileNotFoundError:
            print("Failed to Replace ../resources: File Not Found")
        print("Cleaning up.. (4/4)")
        os.remove("upd.zip")
        shutil.rmtree("temp")
        print("Done!")
    else:
        print("Aborting..")

