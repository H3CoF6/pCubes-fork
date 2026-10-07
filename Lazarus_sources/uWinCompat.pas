{************************************************************}
{                                                            }
{  Unit uWinCompat                                           }
{  2024                                                      }
{                                                            }
{  Cross-platform shim that lets pCubes build with the LCL   }
{  on non-Windows targets. On Windows this unit is a no-op.  }
{************************************************************}

unit uWinCompat;

{$mode delphi}

interface

{$IFNDEF MSWINDOWS}
uses
  Classes, SysUtils, Graphics, LCLType;

const
  INVALID_HANDLE_VALUE: THandle = THandle(-1);
  FILE_ATTRIBUTE_DIRECTORY = $10;

  MIIM_STRING = $00000040;
  MIIM_FTYPE  = $00000100;

  PM_REMOVE = $0001;
  WM_QUIT   = $0012;

  VK_LBUTTON = $01;
  VK_RETURN  = $0D;
  VK_ESCAPE  = $1B;
  VK_SHIFT   = $10;
  VK_CONTROL = $11;
  VK_MENU    = $12;

  TRANSPARENT = 1;

type
  TMsg = LCLType.TMsg;

type
  MENUITEMINFO = record
    cbSize: Cardinal;
    fMask: Cardinal;
    fType: Cardinal;
    fState: Cardinal;
    wID: Cardinal;
    hSubMenu: THandle;
    hbmpChecked: THandle;
    hbmpUnchecked: THandle;
    dwItemData: PtrUInt;
    dwTypeData: PChar;
    cch: Cardinal;
    hbmpItem: THandle;
  end;
  TMenuItemInfo = MENUITEMINFO;

function RGB(r, g, b: Byte): TColor;
function GetRValue(c: TColor): Byte;
function GetGValue(c: TColor): Byte;
function GetBValue(c: TColor): Byte;

function GetAsyncKeyState(vKey: Integer): SmallInt;
function GetLastError: Cardinal;
procedure ZeroMemory(Dest: Pointer; Count: PtrUInt);
procedure DragAcceptFiles(Wnd: THandle; Accept: Boolean);
procedure LockWindowUpdate(Wnd: THandle);
function GetWindowsDirectory(lpBuffer: PChar; uSize: Cardinal): Cardinal;
function CloseHandle(h: THandle): Boolean;

function GetMenuItemInfo(hMenu: THandle; uItem: Cardinal; fByPosition: Boolean;
  lpmii: Pointer): Boolean;
function SetMenuItemInfo(hMenu: THandle; uItem: Cardinal; fByPosition: Boolean;
  lpmii: Pointer): Boolean;

function PeekMessage(var Msg: TMsg; Handle: THandle; Min, Max, Remove: Cardinal): Boolean;
function TranslateMessage(const Msg: TMsg): Boolean;
function DispatchMessage(const Msg: TMsg): PtrInt;
{$ENDIF}

function ToNativePath(const Path: string): string;

implementation

{$IFNDEF MSWINDOWS}
{$IFDEF UNIX}
uses BaseUnix;
{$ENDIF}

function RGB(r, g, b: Byte): TColor;
begin
  Result := TColor(r or (g shl 8) or (b shl 16));
end;

function GetRValue(c: TColor): Byte;
begin
  Result := Byte(c);
end;

function GetGValue(c: TColor): Byte;
begin
  Result := Byte(c shr 8);
end;

function GetBValue(c: TColor): Byte;
begin
  Result := Byte(c shr 16);
end;

function GetAsyncKeyState(vKey: Integer): SmallInt;
begin
  Result := 0;
end;

function GetLastError: Cardinal;
begin
  Result := 0;
end;

procedure ZeroMemory(Dest: Pointer; Count: PtrUInt);
begin
  if (Dest <> nil) and (Count > 0) then
    FillChar(Dest^, Count, 0);
end;

procedure DragAcceptFiles(Wnd: THandle; Accept: Boolean);
begin
end;

procedure LockWindowUpdate(Wnd: THandle);
begin
end;

function GetWindowsDirectory(lpBuffer: PChar; uSize: Cardinal): Cardinal;
begin
  Result := 0;
end;

function CloseHandle(h: THandle): Boolean;
begin
  if h = THandle(-1) then
    Exit(True);
  {$IFDEF UNIX}
  Result := fpclose(cint(h)) = 0;
  {$ELSE}
  Result := True;
  {$ENDIF}
end;

function GetMenuItemInfo(hMenu: THandle; uItem: Cardinal; fByPosition: Boolean;
  lpmii: Pointer): Boolean;
begin
  Result := False;
end;

function SetMenuItemInfo(hMenu: THandle; uItem: Cardinal; fByPosition: Boolean;
  lpmii: Pointer): Boolean;
begin
  Result := True;
end;

function PeekMessage(var Msg: TMsg; Handle: THandle; Min, Max, Remove: Cardinal): Boolean;
begin
  Result := False;
end;

function TranslateMessage(const Msg: TMsg): Boolean;
begin
  Result := False;
end;

function DispatchMessage(const Msg: TMsg): PtrInt;
begin
  Result := 0;
end;
{$ENDIF}

function ToNativePath(const Path: string): string;
{$IFDEF MSWINDOWS}
begin
  Result := Path;
end;
{$ELSE}
var
  i: integer;
begin
  Result := Path;
  for i := 1 to Length(Result) do
    if Result[i] = '\' then
      Result[i] := '/';
end;
{$ENDIF}

end.
