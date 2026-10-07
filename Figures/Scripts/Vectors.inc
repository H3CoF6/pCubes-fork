// local variables begins with "F_". Parameters with "A_". Results with "Ans_".

    function VectorLength( A_x, A_y, A_z);
    begin
        Result := sqrt(A_x^2 + A_y^2 + A_z^2);
    end;

    procedure VectorNormalize( A_x, A_y, A_z);
    begin
        // normalize vector
        F_dn := VectorLength(A_x, A_y, A_z);
        Ans_X := A_x / F_dn;
        Ans_Y := A_y / F_dn;
        Ans_Z := A_z / F_dn;
    end;

    function VectorScalarMultiply( A_x1, A_y1, A_z1, A_x2, A_y2, A_z2);
    begin
        Result := A_x1 * A_x2 + A_y1 * A_y2 + A_z1 * A_z2;
    end;

    procedure VectorMultiply( A_x1, A_y1, A_z1, A_x2, A_y2, A_z2);
    begin
        Ans_X := A_y1 * A_z2 - A_z1 * A_y2;
        Ans_Y := A_z1 * A_x2 - A_x1 * A_z2;
        Ans_Z := A_x1 * A_y2 - A_y1 * A_x2;
    end;

    // Calcs normal to plane with 3 points.
    procedure VectorNormalToPlane( AA_x1, AA_y1, AA_z1, AA_x2, AA_y2, AA_z2, AA_x3, AA_y3, AA_z3);
    begin
        VectorMultiply( AA_x1 - AA_x3, AA_y1 - AA_y3, AA_z1 - AA_z3, AA_x2 - AA_x3, AA_y2 - AA_y3, AA_z2 - AA_z3);
        VectorNormalize( Ans_X, Ans_Y, Ans_Z);
    end;

    // Calcs distance to plane
    function VectorDistanceToPlane( AA_x, AA_y, AA_z, AA_Nx, AA_Ny, AA_Nz, AA_NormalDistance);
    begin
        Result := VectorScalarMultiply( AA_x, AA_y, AA_z, AA_Nx, AA_Ny, AA_Nz) / VectorLength( AA_Nx, AA_Ny, AA_Nz) - AA_NormalDistance;
    end;

    // Calcs angle between v1 and v2
    function VectorAngle2( AA_x1, AA_y1, AA_z1, AA_x2, AA_y2, AA_z2);
    begin
        Result := ArcCos(VectorScalarMultiply( AA_x1, AA_y1, AA_z1, AA_x2, AA_y2, AA_z2) / VectorLength( AA_x1, AA_y1, AA_z1) / VectorLength( AA_x2, AA_y2, AA_z2));
    end;

    // Calcs angle from 2 to 3 while rotating over 1 (No check if not valid, 2 and 3 must have same length and scalar multiplication with 1)
    function VectorRotatingAngle( AA_x1, AA_y1, AA_z1, AA_x2, AA_y2, AA_z2, AA_x3, AA_y3, AA_z3);
    begin
        VectorMultiply( AA_x1, AA_y1, AA_z1, AA_x2, AA_y2, AA_z2);
        F_vx := Ans_X; F_vy := Ans_Y; F_vz := Ans_Z;
        VectorMultiply( AA_x1, AA_y1, AA_z1, AA_x3, AA_y3, AA_z3);
        Result := VectorAngle2( F_vx, F_vy, F_vz, Ans_X, Ans_Y, Ans_Z);
    end;

    // Rotate 1 round normalized 2
    procedure VectorRotatePoint( AA_x1, AA_y1, AA_z1,  AA_x2, AA_y2, AA_z2,  Angle, ANormalize);
    begin
        F_ca := Cos(Angle);
        F_sa := Sin(Angle);
        F_c2 := 1 - Cos(Angle);

        if ANormalize then begin
            VectorNormalize( AA_x2, AA_y2, AA_z2);
            AA_x2 := Ans_X; AA_y2 := Ans_Y; AA_z2 := Ans_Z;
        end;

        Ans_X := AA_x1 * (AA_x2 * F_c2 * AA_x2 + F_ca) +
                 AA_y1 * (AA_y2 * F_c2 * AA_x2 - F_sa * AA_z2) +
                 AA_z1 * (AA_z2 * F_c2 * AA_x2 + F_sa * AA_y2);

        Ans_Y := AA_x1 * (AA_x2 * F_c2 * AA_y2 + F_sa * AA_z2) +
                 AA_y1 * (AA_y2 * F_c2 * AA_y2 + F_ca) +
                 AA_z1 * (AA_z2 * F_c2 * AA_y2 - F_sa * AA_x2);

        Ans_Z := AA_x1 * (AA_x2 * F_c2 * AA_z2 - F_sa * AA_y2) +
                 AA_y1 * (AA_y2 * F_c2 * AA_z2 + F_sa * AA_x2) +
                 AA_z1 * (AA_z2 * F_c2 * AA_z2 + F_ca);
    end;
