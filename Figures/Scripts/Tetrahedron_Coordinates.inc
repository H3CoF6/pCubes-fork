        if not VarExists('W') then
            W := 0.5;

        // Vertices (corners)

        Vx[0] := W; Vy[0] :=-W; Vz[0] := W; 
        Vx[1] :=-W; Vy[1] := W; Vz[1] := W; 
        Vx[2] := W; Vy[2] := W; Vz[2] :=-W; 
        Vx[3] :=-W; Vy[3] :=-W; Vz[3] :=-W; 


        // Centers

        Cx[0] :=-W/3; Cy[0] := W/3; Cz[0] :=-W/3; 
        Cx[1] := W/3; Cy[1] :=-W/3; Cz[1] :=-W/3; 
        Cx[2] :=-W/3; Cy[2] :=-W/3; Cz[2] := W/3; 
        Cx[3] := W/3; Cy[3] := W/3; Cz[3] := W/3; 


        // Edges

        Ex[0] :=-W; Ey[0] := 0; Ez[0] := 0; 
        Ex[1] := W; Ey[1] := 0; Ez[1] := 0; 
        Ex[2] := 0; Ey[2] :=-W; Ez[2] := 0; 
        Ex[3] := 0; Ey[3] := W; Ez[3] := 0; 
        Ex[4] := 0; Ey[4] := 0; Ez[4] :=-W; 
        Ex[5] := 0; Ey[5] := 0; Ez[5] := W; 
