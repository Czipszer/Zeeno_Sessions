import argparse
import csv
from queue import Empty

from typing import List
from dataclasses import dataclass
from datetime import datetime
from pprint import pprint

# Definition class for flight
@dataclass
class Flight:
    flight_no: str
    origin: str
    destination: str
    departure: datetime
    arrival: datetime
    base_price: float
    bag_price: float
    bags_allowed: int

    # def __repr__(self) -> str:
    #     return str(self)

    # def __str__(self) -> str:
    #     return f"\nFlight {self.flight_no}"

# Definition class for airport
@dataclass
class Airport:
    name: str
    flights: List[Flight]

    def add_flight(self, new_flight):
        self.flights.append(new_flight)

    # def __str__(self) -> str:
    #     return f"Airport '{self.name}' {self.flights}\n"

# BFS search algorithm
def search(airports, now, destination, bags, my_flight, visited, my_possible_flights):
    if now == destination:
        my_possible_flights.append(my_flight)
        return

    for next_destination in airports[now].flights:
        if next_destination.destination not in visited:
            if int(next_destination.bags_allowed) >= bags:
                waiting = 1
                if len(my_flight) != 0:
                    waiting = datetime.fromisoformat(next_destination.departure) - datetime.fromisoformat(my_flight[-1].arrival)
                if 3600 >= divmod(waiting.total_seconds) <= 21600:
                    visited.append(next_destination)
                    my_flight.append(next_destination)
                    search(airports, next_destination.destination, destination, bags, my_flight.copy(), visited.copy(), my_possible_flights)
                    

if __name__ == '__main__':
    # Command line arguments parser
    parser = argparse.ArgumentParser()
    parser.add_argument('file', type=str)
    parser.add_argument('origin', type=str)
    parser.add_argument('destination', type=str)
    parser.add_argument('--bags', type=int, default=0)
    parser.add_argument('--return', action='store_true', default=False)
    arguments = parser.parse_args()
    # pprint(arguments)

    # Load data from CVS
    with open(arguments.file) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        next(csv_reader)
        flights = [Flight(*row) for row in csv_reader]
    # list(map(pprint, flights))

    # Full class with data
    airports = {}
    for f in flights:
        airport = airports.get(f.origin)
        if airport is None:
            airport = Airport(f.origin, [])
            airports[f.origin] = airport
        airport.add_flight(f)     
    # pprint(airports)

    visited = []
    my_flight = []
    my_possible_flights = []
    
    search(airports, arguments.origin, arguments.destination, arguments.bags, my_flight, visited, my_possible_flights)



        