BEGIN
    IF size = capacity THEN

        IF capacity = 0 THEN
            newCapacity = 2
        ELSE
            newCapacity = capacity * 2
        END IF

        p = REALLOCATE(data, newCapacity)

        IF p = NULL THEN
            RETURN FAILURE
        ELSE
            data = p
            capacity = newCapacity
        END IF

    END IF

    data[size] = donor
    size = size + 1

    RETURN SUCCESS
END
