// Prototype: Not so efficient

// First we define aux methods and types

let chessArrayRow (j: int) = 2 * j - 1
let chessArrayCol (j: int) = 4 * j - 2

type Kind =
    | King
    | Queen
    | Rook
    | Bishop
    | Knight
    | Pawn

type Color =
    | White
    | Black

type ChessRecord =
    { kind: Kind
      column: int
      row: int }

type ChessSummary =
    { white: ChessRecord list
      black: ChessRecord list }

let internal second (_, b) = b

// second we write bigger functions
// we hide internal functions within function bodies
// this is like "encapsulation" but we aren't hiding information but internal mechanics

let summarizeChess (board: string array) =
    let colorAndKind (column: int) (row: int) =
        match board.[row].[column] with
        | 'K' -> Some(White, King)
        | 'Q' -> Some(White, Queen)
        | 'R' -> Some(White, Rook)
        | 'B' -> Some(White, Bishop)
        | 'N' -> Some(White, Knight)
        | 'P' -> Some(White, Pawn)
        | 'k' -> Some(Black, King)
        | 'q' -> Some(Black, Queen)
        | 'r' -> Some(Black, Rook)
        | 'b' -> Some(Black, Bishop)
        | 'n' -> Some(Black, Knight)
        | 'p' -> Some(Black, Pawn)
        | _ -> None

    let intermediate =
        seq {
            for row = 8 downto 1 do
                for column = 1 to 8 do
                    match colorAndKind (chessArrayCol column) (chessArrayRow row) with
                    | Some (color, kind) ->
                        yield (color,
                               { kind = kind
                                 column = column
                                 row = row })
                    | None -> yield! Seq.empty // yield nothing
        }

    let white =
        Seq.filter (fun (c, _) -> c = White) intermediate
        |> Seq.map second
        |> List.ofSeq

    let black =
        Seq.filter (fun (c, _) -> c = Black) intermediate
        |> Seq.map second
        |> List.ofSeq

    { ChessSummary.white = white
      ChessSummary.black = black }

let stringFromRecord (row: ChessRecord) =
    let colToChar (j: int) = 'a' + char (j - 1)
    let rowToChar (j: int) = '1' + char (8 - j)

    let kindToChar (k: Kind) =
        match k with
        | King -> "K"
        | Queen -> "Q"
        | Rook -> "R"
        | Bishop -> "B"
        | Knight -> "N"
        | Pawn -> ""

    match row with
    | { kind = k; column = c; row = r } -> kindToChar k + string (colToChar c) + string (rowToChar r)

let sortWith (color: Color) (left: ChessRecord) (right: ChessRecord) =
    let kindToOrder (k: Kind) =
        match k with
        | King -> 0
        | Queen -> 1
        | Rook -> 2
        | Bishop -> 3
        | Knight -> 4
        | Pawn -> 5

    let kindLess = kindToOrder left.kind < kindToOrder right.kind
    let kindMore = kindToOrder left.kind > kindToOrder right.kind
    let columnLess = left.column < right.column
    let columnMore = left.column > right.column
    let rowLess = left.row < right.row
    let rowMore = left.row > right.row

    if kindLess then -1
    else if kindMore then 1
    else if rowLess then if color = White then 1 else -1
    else if rowMore then if color = White then -1 else 1
    else if columnLess then -1
    else if columnMore then 1
    else 0

let printRecords (c: Color) (rows: ChessRecord seq) =
    printf "%s: " (if c = White then "White" else "Black")
    rows
    |> Seq.sortWith (sortWith c)
    |> Seq.map stringFromRecord
    |> String.concat ","
    |> System.Console.WriteLine

let realMain () =
    let exampleChessBoard =
        seq {
            for _ in 1 .. 17 do
                yield System.Console.ReadLine()
        }
        |> Array.ofSeq

    let { white = white; black = black } = summarizeChess exampleChessBoard
    printRecords White white
    printRecords Black black
    0

let printTest () =
    let caseTest (correct: string) (column: int) (row: int) (i: int) =
        let codeOutput =
            (stringFromRecord
                { kind = Pawn
                  column = column
                  row = row })
        printfn "Test Case #%d" i
        printfn "Input (column, row) = (%d, %d)" column row
        printfn "Correct: %s" correct
        printfn "Code Output: %s" codeOutput
        printfn "Correct = Code Output? %A" (correct = codeOutput)
        printfn ""
    caseTest "c5" 3 5 0
    caseTest "b2" 2 2 1
    caseTest "f7" 6 7 2
    caseTest "a8" 1 8 3
    caseTest "h8" 8 8 4
    caseTest "a1" 1 1 5

let sortWithTest () =
    let sortWithTestCase (expected: int) (color: Color) (left: ChessRecord) (right: ChessRecord) =
        printfn "sortWithTest color = %A, left = %s, right = %s, expected = %d, actual = %d" color
            (stringFromRecord left) (stringFromRecord right) expected (sortWith color left right)

    let ra8 =
        { kind = Rook
          column = 1
          row = 1 }

    let pn6 =
        { kind = Pawn
          column = 8
          row = 3 }

    let ng8 =
        { kind = Knight
          column = 7
          row = 1 }

    let nc6 =
        { kind = Knight
          column = 3
          row = 3 }

    sortWithTestCase -1 Black ra8 pn6
    sortWithTestCase 1 Black pn6 ra8
    sortWithTestCase -1 White ra8 pn6
    sortWithTestCase 1 White pn6 ra8
    sortWithTestCase 1 White ng8 nc6
    sortWithTestCase -1 Black ng8 nc6

[<EntryPoint>]
let main _ = realMain ()
