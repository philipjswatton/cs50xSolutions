--SELECT * FROM crime_scene_reports; --start getting a sense of the data
--SELECT * FROM crime_scene_reports WHERE street = "Chamberlin Street" AND year = 2020 AND month = 7 AND day = 28; --look at the specific case
--SELECT * FROM interviews WHERE year = 2020 AND month = 7 AND day = 28; -- read interviews mentioning a courthouse
--SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month =7 AND day = 28 AND hour =10; -- look at cars arriving and leaving from 10.00 to 10.59
--SELECT * FROM atm_transactions WHERE year = 2020 AND month =7 AND day = 28 and atm_location = "Fifer Street"; --look at transactions
--SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month =7 AND day = 28 and atm_location = "Fifer Street")); --match transactions to people
--SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month =7 AND day = 28 AND hour =10 AND activity = "exit") AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month =7 AND day = 28 and atm_location = "Fifer Street")); --narrowing down the options
--SELECT * FROM flights WHERE year = 2020 AND month =7 AND day = 29; --earliest flight the day after is id = 36
--SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36); who was on the earliest flight
--SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month =7 AND day = 28 AND hour =10 AND activity = "exit") AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month =7 AND day = 28 and atm_location = "Fifer Street")) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36); --further narrowing the options
--SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month =7 AND day = 28 AND hour =10 AND minute < 30 AND activity = "exit") AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month =7 AND day = 28 and atm_location = "Fifer Street")) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month =7 AND day = 28); --add phone call, narrow the time window for exiting to before 10.30, find out the person is ernest
--SELECT * FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE id = 36); --find out where ernest went
SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller = "(367) 555-5533" AND year = 2020 AND month =7 AND day = 28 AND duration < 60) -- find the accomplice

-- crime scene ID = 295
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Court Logs:
-- 258 | 2020 | 7 | 28 | 10 | 8 | entrance | R3G7486
-- 259 | 2020 | 7 | 28 | 10 | 14 | entrance | 13FNH73
-- 260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
-- 261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
-- 262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
-- 263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
-- 264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
-- 265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
-- 266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
-- 267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55
-- 268 | 2020 | 7 | 28 | 10 | 35 | exit | 1106N58
-- 269 | 2020 | 7 | 28 | 10 | 42 | entrance | NRYN856
-- 270 | 2020 | 7 | 28 | 10 | 44 | entrance | WD5M8I6
-- 271 | 2020 | 7 | 28 | 10 | 55 | entrance | V47T75I


--686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X