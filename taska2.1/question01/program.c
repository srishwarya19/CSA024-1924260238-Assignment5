BEGIN
    INPUT number

    IF number < 10 THEN
        RETURN number
    ELSE
        sum = 0
        WHILE number > 0
            digit = number MOD 10
            sum = sum + digit
            number = number DIV 10
        END WHILE

        RETURN DIGITALROOT(sum)
    END IF
END
