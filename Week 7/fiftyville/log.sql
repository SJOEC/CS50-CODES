-- Keep a log of any SQL queries you execute as you solve the mystery.
-- the theft took place on July 28, 2021 and that it took place on Humphrey Street.

-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,
--I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- ten minutes after the theft the tief get into a car and drive away


SELECT description FROM crime_scene_reports WHERE day = 28 AND street = 'Humphrey Street';

/*
Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
Littering took place at 16:36. No known witnesses.
*/

SELECT license_plate FROM bakery_security_logs WHERE hour > 8 AND hour < 11 AND activity = 'exit' ORDER BY name; -- looking for any person in the bakery at that time

SELECT name, people.license_plate, hour, minute, day, activity
    FROM bakery_security_logs
        JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND month = 7 AND year = 2021 AND hour > 8 AND hour <= 11 AND activity LIKE '%exit%' ORDER BY hour, minute; -- looking for the names for the people with a log in the bakery at that time

SELECT name,transcript FROM interviews WHERE day = 28 AND month = 7 AND year = 2021; -- looking for the theft interviews

SELECT name, caller, receiver, duration, day FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number WHERE name IN
(SELECT name
    FROM bakery_security_logs
        JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND month = 7 AND year = 2021 AND hour > 8 AND hour <= 11 AND activity LIKE '%exit%' ORDER BY hour, minute) AND day = 28 AND month = 7 AND year = 2021 AND duration < 100; -- looking for call callers 10 mminutes after crime


SELECT name FROM people WHERE phone_number IN (
SELECT receiver FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number WHERE name IN
(SELECT name
    FROM bakery_security_logs
        JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND month = 7 AND year = 2021 AND hour > 8 AND hour <= 11 AND activity LIKE '%exit%' ORDER BY hour, minute) AND day = 28 AND month = 7 AND year = 2021 AND duration < 100); -- looking for call recievers 10 mminutes after crime


SELECT flights.id, city, full_name, destination_airport_id, hour, minute, day
    FROM flights
        JOIN airports ON airports.id = destination_airport_id
WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id = 8 ORDER BY hour; -- looking for flights the next day of the theft | flight 36


SELECT name, people.passport_number
    FROM passengers
        JOIN people ON people.passport_number = passengers.passport_number
WHERE name IN
    (SELECT name FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number WHERE name IN (SELECT name
        FROM bakery_security_logs
            JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND month = 7 AND year = 2021 AND hour > 8 AND hour <= 11 AND activity LIKE '%exit%' ORDER BY hour, minute) AND day = 28 AND month = 7 AND year = 2021 AND duration < 100)
    AND flight_id = 36; -- people that take a flight and call the thief accomplice



SELECT name, person_id,bank_accounts.account_number, amount, transaction_type
    FROM atm_transactions
        JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
        JOIN people ON people.id = bank_accounts.person_id
WHERE day = 28 OR day = 29 AND month = 7 AND year = 2021 ORDER BY name;  -- looking for atm transactions | Bruce withdraw the same day in the morning


SELECT name FROM people WHERE name IN
(SELECT name
    FROM atm_transactions
        JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
        JOIN people ON people.id = bank_accounts.person_id
WHERE day = 28 OR day = 29 AND month = 7 AND year = 2021 ORDER BY name)
    AND name IN (SELECT name FROM people WHERE phone_number IN (
SELECT receiver FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number WHERE name IN
(SELECT name
    FROM bakery_security_logs
        JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND month = 7 AND year = 2021 AND hour > 8 AND hour <= 11 AND activity LIKE '%exit%' ORDER BY hour, minute) AND day = 28 AND month = 7 AND year = 2021 AND duration < 100)); -- jack buy the ticket

SELECT phone_number FROM people WHERE name = 'Jack'; -- Sofia Call Jack








