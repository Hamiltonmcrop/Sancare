import os
from os import system
from random import randint

gametitle = "Castle Dungeons - an interactive story game"
print(gametitle)

class Character:
    def __init__(self, name, race, char_class, strength, magic, dexterity, life):
        self.name = name
        self.race = race
        self.char_class = char_class
        self.strength = strength
        self.magic = magic
        self.dexterity = dexterity
        self.life = life

    def __str__(self):
        return f"""
        Name: {self.name}
        Race: {self.race}
        Class: {self.char_class}
        Strength: {self.strength}
        Dexterity: {self.dexterity}
        Magic: {self.magic}
        Life: {self.life}
        """


class PlayerCharacter(Character):
    def __init__(self, name, race, char_class, strength, magic, dexterity, life):
        super().__init__(name, race, char_class, strength, magic, dexterity, life)

    def modify_skills(self):
        print("To modify your skills, roll a six-face die for each skill.")
        input("Press Enter to roll for Strength")
        roll = randint(1, 6)
        print("You rolled: " + str(roll))
        self.strength += roll

        input("Press Enter to roll for Dexterity")
        roll = randint(1, 6)
        print("You rolled: " + str(roll))
        self.dexterity += roll

        input("Press Enter to roll for Life")
        roll = randint(1, 6)
        print("You rolled: " + str(roll))
        self.life += roll

        input("Press Enter to continue...")

    def show_character_sheet(self):
        print(self)


def create_character():
    cls()
    character_name = input("""
    Let's begin by creating your character.
    What is your character name?
    > """)

    character_race = None
    while character_race is None:
        race_choice = input("""
        Choose your character race from the list below by entering the relevant number:
        1 - Elf
        2 - Dwarf
        > """)
        if race_choice == "1":
            character_race = "Elf"
        elif race_choice == "2":
            character_race = "Dwarf"
        else:
            print("Not a valid choice, try again")

    character_class = None
    while character_class is None:
        class_choice = input("""
        Choose your character class from the list below by entering the relevant number:
        1 - Warrior
        2 - Wizard
        > """)
        if class_choice == "1":
            character_class = "Warrior"
        elif class_choice == "2":
            character_class = "Wizard"
        else:
            print("Not a valid choice, try again")

    return PlayerCharacter(
        character_name,
        character_race,
        character_class,
        5,
        0,
        3,
        10  # Initial values for strength, magic, dexterity, and life
    )


def cls():
    os.system('clear')


def Intro():
    print("")
    print("Castle dungeons - An interactive fiction game in Python.")
    print("")
    print("In this adventure, you are the hero.")
    print("Your choices, skills, and a bit of luck, will influence the outcome of the game.")
    print("")
    print("An evil sorcerer is holding your fellow adventurers prisoners.")
    print("Will you succeed to free your friends from the castle dungeons, or peril trying?")
    print(" ")
    input("Press Enter to start...")


def create_character_skill_sheet(player):
    cls()
    print("""
    Now let's determine your character's skills, which you will use throughout the game.
    In this game, your character has four skills:
    
    - Strength, which you will use in combat or any strength test
    - Dexterity, which you will use in any ability test
    - Magic, which you will use whenever you need to cast a spell or use/inspect a magical item or place
    - Life, which determines your life energy, points will be lost when hurt, 
      and whenever Life reaches 0, your character dies.

    
    Depending on your race and class, you will have a certain point-base already calculated by the game.
    You will shortly be able to increase your skills by rolling a 6-face die.

    Here is your base Character Skills Sheet:
    """)
    player.modify_skills()


def Scene_1(player):
    cls()
    choice = None  
    while choice is None:
        user_input = input("""
    You have entered the Castle Dungeons.. 
    It is dark, however thankfully your torch is lit and you can see up to 20 feet away from you.
    The stone walls are damp, the smell of rats and orcs is strong. 
    You walk down a narrow corridor, until you reach a thick stone wall.

    The corridor continues on the left, and on the right.

    What do you do?

    1 - Turn left
    2 - Turn right    
    > """)
        if user_input == "1" or user_input == "turn left":
            choice = "1"
            Scene_2(player)
        elif user_input == "2" or user_input == "turn right":
            choice = "2"
            Scene_3(player)
        else:
            print("""
            Not a valid choice, type a number or "turn left" / "turn right"
            """)


# Remaining functions (Scene_2, Scene_3, skill_check, combat) stay unchanged
def Scene_2(player):
    cls()
    choice = None
    while choice is None:
        user_input=input("""
    From the darkness behind you.. you hear a strange noise.

    What do you do?

    1 - Continue walking
    2 - Stop to listen

    > """)
        if user_input=="1" or user_input=="continue":
            choice="1"
            combat(player)
        elif user_input=="2" or user_input=="stop":
            choice="2"
            skill_check(player)
        else:
            print("""
            Not a valid choice, type a number or "continue" / "stop"
            """)

def Scene_3(player):
    cls()
    choice = None
    while choice is None:
        user_input=input("""
    From the darkness ahead of you.. you hear a strange noise.

    What do you do?

    1 - Continue walking
    2 - Stop to listen

    > """)
        if user_input=="1" or user_input=="continue":
            choice="1"
            combat(player)
        elif user_input=="2" or user_input=="stop":
            choice="2"
            skill_check(player)
        else:
            print("""
            Not a valid choice, type a number or - "continue" / "stop"
            """)

def skill_check(player):
    cls()
    print("A giant rock falls from the ceiling, roll a die to see if you can dodge it.. or you will be crashed by it!")
    roll=randint(1,6)
    print("You rolled: "+str(roll))
    if roll + player.dexterity > 10:
        print ("""
        You dodge the stone and survive! Danger is not over though..
        The strange noise in the darkness continues, and it feels a lot closer now..""")
        input("Press Enter to continue...")
        combat(player)
    else:
        print("You are smashed by the rock.. You die. The game is over.")
        input("Press Enter to exit the game.")

def combat(player):
    cls()
    print("A horrible orc attacks you!")
    input("Press Enter to combat...")
    orc = [10, 14]
    while orc[1] > 0 or player.life > 0: 
        char_roll=randint(1,6)
        print("You rolled: "+str(char_roll))
        monst_roll=randint(1,6)
        print("The monster rolled: "+str(monst_roll))
        if char_roll + player.strength >= monst_roll + orc[0]:
            print("You hit the monster!")
            orc[1] -= randint(1,6)
        else: 
            print("The monster hits you!")
            player.life -= randint(1,6)
    if player.life > 0:
        print("You defeated the orc, congratulations!")
        input("Press Enter to exit the game")
    else:
        print("You lost.. your friends will never be freed.. and you're dead.")
        input("Press Enter to exit the game")

#Scene_1()
# Main game logic
Intro()
player = create_character()
create_character_skill_sheet(player)
Scene_1(player)
