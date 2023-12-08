import re

string = """1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet"""

result = sum([int(list(filter(lambda x: x.isdigit(), [c for c in line]))[0] + list(filter(lambda x: x.isdigit(), [c for c in line]))[-1]) for line in string.split()])

red_count = 12
green_count = 13
blue_count = 14

string = """Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"""


def parse_game(game_string):
    keys = ['Game', 'red', 'blue', 'green']
    values = [sum([int(''.join(c for c in x if c.isdigit())) for x in list(filter(lambda info: key in info, re.split(',|;|:', game_string)))]) for key in keys]
    return dict((key, value) for key, value in zip(keys, values))

games = [parse_game(game_string) for game_string in string.split('\n')]
total = sum([game['Game'] for game in games if game['red'] <= red_count and game['green'] <= green_count and game['blue'] <= blue_count])
print(total)
    