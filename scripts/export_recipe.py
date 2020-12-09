# Export to database recipes

import mysql.connector
import sys
import os
import csv


# Read directory with recipe csv files
def read_recipes():
    if len(sys.argv) > 1:
        recipes_dir = sys.argv[1]
    else:
        recipes_dir = "../data/recipes"

    recipe_ingredients = list()
    for root, dirs, files in os.walk(recipes_dir):
        files_csv = [os.path.join(root, f) for f in files if os.path.isfile(os.path.join(root, f))
                     and os.path.splitext(f)[1] == ".csv"]

        for f_csv in files_csv:
            k = os.path.basename(os.path.splitext(f_csv)[0])
            with open(f_csv, encoding="utf-8") as fid:
                reader = csv.reader(fid)
                for row in reader:
                    recipe_ingredients.append(["\'" + k + "\'", "\'" + row[0].lower() + "\'", row[1]])
    return recipe_ingredients


def main():
    mydb = mysql.connector.connect(
        host="127.0.0.1",
        port=3306,
        user="root",
        password="iago",
        database="clever_food_sch"
    )
    mycursor = mydb.cursor()

    # Read files with recipes and get recipes with parameters
    records = read_recipes()

    sql = "insert into recipes(name, product, weight) values({0}, {1}, {2})"
    for r in records:
        try:
            mycursor.execute(sql.format(r[0],r[1],r[2]))
        except Exception as e:
            print(r)
            print(e)

    mydb.commit()
    pass


if __name__ == "__main__":
    main()
