

import urllib.request
import json

URL = "https://pypi.org/pypi/sampleproject/json"

def main():
    
    with urllib.request.urlopen(URL) as response:
        data_bytes = response.read()          
        data_str = data_bytes.decode("utf-8") 

    data = json.loads(data_str)

    releases = data.get("releases", {})

    for version, files in releases.items():
        for file_info in files:
            filename = file_info.get("filename")
            if filename is not None:
                print(filename)

if __name__ == "__main__":
    main()
