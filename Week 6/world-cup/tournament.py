# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # initialize  a list to store the teams and their ratings
    teams = []

    # while the file is open
    with open(sys.argv[1], "r") as file:
        # reader will be a dictionary of each row
        reader = csv.DictReader(file)
        # add each row (each dictionary) into the teams list
        for row in reader:
            row["rating"] = int(row["rating"])
            teams.append(row)

    counts = {}


    for i in range(5):

        winner = simulate_tournament(teams)

        # if winner already win a tournament, add 1 victory
        if winner in counts:

            counts[winner] += 1

        else:

        # else add set wins into 1, if it isnt create yet, the code will create ir automatically
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""

    # if isn't a winner yet
    while len(teams) != 1:
        # simulate another round
        teams = simulate_round(teams)
    # if is a winner, return the name
    return teams[0]["team"]


if __name__ == "__main__":
    main()
