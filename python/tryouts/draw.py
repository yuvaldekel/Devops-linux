# Imports
import random

# Constatnts
TOTAL_GAMES = 2


def main():
    matches = []
    teams = {}

    # Read teams
    while True:
        team_name = input("Enter team name -> ")
        
        # Exit
        if team_name == 'exit':
            break

        teams[team_name] = TOTAL_GAMES

    # Go over all the teams
    for team in teams.keys():

        # Peak games 
        for _ in range(teams[team]):
            
            second_team, second_games = random.choice(list(teams.items()))

            # The games have already been chosen
            while {second_team, team} in matches or second_team == team or second_games == 0:
                second_team, second_games  = random.choice(list(teams.items()))

            teams[second_team] = teams[second_team] - 1
            matches.append({second_team, team})
        
        teams[team] = 0

    print(matches)
    print(teams)


if __name__ == "__main__":
    main()