BEGIN
    INPUT index, newUnits

    SEEK file TO index * SIZEOF(stock)

    READ stock FROM file

    IF READ FAILS THEN
        RETURN FAILURE
    END IF

    stock.units = newUnits

    SEEK file TO index * SIZEOF(stock)

    WRITE stock TO file

    IF WRITE FAILS THEN
        RETURN FAILURE
    END IF

    RETURN SUCCESS
END
