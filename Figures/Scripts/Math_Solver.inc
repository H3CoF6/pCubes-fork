// Bisection method to solve f(x)=0.
// Function Equation_To_Solve must be defined.
// f(x1) and f(x2) must have different signes

    function Math_Solver_Sign(A_x1);
    begin
        if A_x1 > 0 then
            Result := 1
        else if (A_x1 < 0) then
            Result := -1
        else
            Result := 0;
    end;

    function Math_Solver_Solve_Equation( A_x1, A_x2);
    begin
        F_Max_iterations := 60;
        F_x1 := A_x1;
        F_x2 := A_x2;
        F_s1 := Math_Solver_Sign(Equation_To_Solve(F_x1));
        F_s2 := Math_Solver_Sign(Equation_To_Solve(F_x2));
        if F_s1 * F_s2 <> -1 then
            ShowMessage('Math_Solver_Solve_Equation:' + Chr(13) + '    f(x1) and f(x2) must have different signes');
        for F_i := 0 to F_Max_iterations do begin
            F_x3 := (F_x1 + F_x2) / 2;
            F_s3 := Math_Solver_Sign(Equation_To_Solve(F_x3));
            if (F_s3 = 0) or (F_x3 = F_x1) or (F_x3 = F_x2) then
                break;
            if F_s1 = F_s3 then begin
                F_x1 := F_x3;
                F_s1 := F_s3;
            end else if F_s2 = F_s3 then begin
                F_x2 := F_x3;
                F_s2 := F_s3;
            end else
                break;
        end;
        Result := F_x3;
    end;
