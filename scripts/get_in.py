import argparse
import os
import plistlib
from pathlib import Path

BASE_PATH = Path(os.path.expanduser("~/Library/Application Support/Clipy"))
TARGET_PATH = Path("./in.txt")


def main(limit: int):
    files = sorted(
        BASE_PATH.glob("*.data"), key=lambda x: x.stat().st_mtime, reverse=True
    )

    with TARGET_PATH.open("w") as f:
        for file in files[:limit][::-1]:
            with file.open("rb") as fp:
                data = plistlib.load(fp)
                f.write(data["$objects"][5] + "\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", type=int, default=3)
    args = parser.parse_args()
    main(args.n)
