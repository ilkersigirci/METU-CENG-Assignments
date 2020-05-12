


void championshipTests() {
    HEADER("CHAMPIONSHIP TESTS");
    TESTHEADER("ADD NEW RACE TEST");
    Race r1 = Race("test");
    r1.addCartoRace();
    r1.addCartoRace();
    r1.addCartoRace();
    r1.addCartoRace();
    Championship cs1 = Championship();
    cs1.addNewRace(r1);
    cs1.addNewRace("test2");
    cs1.addNewRace("test3");
    printResult(cs1.getRaces().size() == 3);
    TESTHEADER("INDEXING TESTS");
    printResult(cs1["test"].getRaceName() == "test" &&
                cs1["test2"].getRaceName() == "test2" &&
                cs1["test3"].getRaceName() == "test3");
    TESTHEADER("ADD LAP TESTS");
    cs1.addLap("test");
    cs1.addLap("test");
    cs1.addLap("test");
    cs1.addLap("test2");
    cs1.addLap("test2");
    cs1.addLap("test3");
    Race race = cs1["test"];
    TESTNAME("NO TESTS HERE");
    /*
    printResult(cs1["test"].getLapCount() == 3 &&
                cs1["test2"].getLapCount() == 2 &&
                cs1["test3"].getLapCount() == 1);
                */
    TESTHEADER("STREAM OPERATOR TEST");
    r1.addCartoRace();
    r1.addCartoRace();
    r1.addCartoRace();
    r1.addCartoRace();
    r1.addCartoRace();
    r1.addCartoRace();
    r1.addCartoRace();
    r1.addCartoRace();
    r1.addCartoRace();
    r1.addCartoRace();
    r1.addCartoRace();
    Championship cs2 = Championship();
    cs2.addNewRace(r1);
    cs2.addNewRace("test4");
    cs2.addNewRace("test5");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");
    cs2.addLap("test");

    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");
    cs2.addLap("test4");

    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");
    cs2.addLap("test5");

    PRINT("\tCHECK WITH YOUR EYES");
    std::cout << cs2;

    TESTHEADER("REMOVE RACE TEST");
    cs1.removeRace("test");
    cs1.removeRace("test2");
    cs1.removeRace("test3");
    printResult(cs1.getRaces().size() == 0);

    if (FAIL_COUNT > 0)
        PRINT("\n" << "YOU HAVE FAILED IN " << FAIL_COUNT << " TESTS IN CHAMPIONSHIP" << "\n");

    TOTAL_FAILS += FAIL_COUNT;
    FAIL_COUNT = 0;
    FOOTER;
}