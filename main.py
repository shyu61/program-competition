import os

def main():
    files = os.listdir("./code/problems")
    for file in files:
        basename = file.split(".")[0]
        number = int(basename.split("main")[1])
        format_number = f"{number:03}"
        os.rename(f"./code/problems/{file}", f"./code/problems/main{format_number}.cpp")




if __name__ == "__main__":
    main()
