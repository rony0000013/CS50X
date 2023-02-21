-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street" AND month = 7 AND year = 2021 AND day = 28;

SELECT * FROM interviews WHERE month = 7 AND year = 2021 AND day = 28;

SELECT * FROM bakery_security_logs WHERE month = 7 AND year = 2021 AND day = 28 AND hour = 10 AND minute > 9 AND minute < 21;

SELECT * FROM people WHERE id In (SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND month = 7 AND year = 2021 AND day = 28))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE
month = 7 AND year = 2021 AND day = 28 AND hour = 10 AND minute > 9 AND minute < 21 AND activity = "exit");

SELECT * FROM phone_calls WHERE month = 7 AND year = 2021 AND day = 28 AND duration < 61;

SELECT * FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE month = 7 AND year = 2021 AND day = 28 AND duration < 61 AND caller IN
(SELECT phone_number FROM people WHERE id In
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND month = 7 AND year = 2021 AND day = 28))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE
month = 7 AND year = 2021 AND day = 28 AND hour = 10 AND minute > 9 AND minute < 21 AND activity = "exit")));

SELECT * FROM flights WHERE month = 7 AND year = 2021 AND day = 29 ORDER BY hour LIMIT 1;

SELECT * FROM airports WHERE id =
(SELECT destination_airport_id FROM flights WHERE month = 7 AND year = 2021 AND day = 29 ORDER BY hour LIMIT 1);

SELECT * FROM passengers WHERE flight_id =
(SELECT id FROM flights WHERE month = 7 AND year = 2021 AND day = 29 ORDER BY hour LIMIT 1);

