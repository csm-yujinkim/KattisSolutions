module Program

module internal Normal =
    let public makeTable =  // FIXME: Verb 'make' is misleading because it implies it creates
                            // a new table instance each time it is invoked, even though
                            // the variable is created at startup and so no new instance
                            // is made each time
        let evenRow = "+---+---+---+---+---+---+---+---+" |> Seq.toArray
        let oddFirstRow = "|...|:::|...|:::|...|:::|...|:::|" |> Seq.toArray
        let oddSecondRow = "|:::|...|:::|...|:::|...|:::|...|" |> Seq.toArray
        [| for _ = 0 to 3 do
            yield Array.copy evenRow
            yield Array.copy oddFirstRow
            yield Array.copy evenRow
            yield Array.copy oddSecondRow
           yield Array.copy evenRow |]

    let public showTable (table: char array array) =
        table
        |> Array.map System.String
        |> Array.iter System.Console.WriteLine

    let public removeColorTag (line: string) =
        if line.Length >= 7 then line.Substring 7 else ""

    let public commaSeparate (line: string) =
        match line.Length with
        | 0 -> [||]
        | _ ->
            line.Split [| ',' |]
            |> Array.map Seq.rev
            |> Array.map Array.ofSeq
            |> Array.map System.String

module internal ColorDependent =
    let private decodeColumn (s: string) =
        let char_a = 'a' |> int
        let coded = int (Seq.item 1 s) - char_a
        coded * 4 + 2

    let private decodeRow (s: string) =
        let number1 = '1' |> int
        let coded = int (Seq.item 0 s) - number1
        let inverted = coded * 2 + 1
        16 - inverted // 16 is the last index of the columns

    let private decodeUnreachableException (field: string) =
        System.Exception(sprintf "Unreachable. Length = %d. Contents = %s" field.Length field)

    let private decodeKindWhite (reversedField: string) =
        match reversedField.Length with
        | 2 -> 'P'
        | 3 -> Seq.item 2 reversedField
        | _ -> raise (decodeUnreachableException reversedField)

    let private decodeKindBlack (reversedField: string) =
        match reversedField.Length with
        | 2 -> 'p'
        | 3 -> Seq.item 2 reversedField |> System.Char.ToLower
        | _ -> raise (decodeUnreachableException reversedField)

    let private processInternal (decodeKind: string -> char) (rawLine: string) (table: char array array) =
        let fields =
            rawLine
            |> Normal.removeColorTag
            |> Normal.commaSeparate
            |> Array.map
                (fun reversedField -> decodeKind reversedField, decodeRow reversedField, decodeColumn reversedField)

        fields |> Array.iter (fun (kind, row, column) -> table.[row].[column] <- kind)

    let public processWhite = processInternal decodeKindWhite
    let public processBlack = processInternal decodeKindBlack

let realMain () =
    let table = Normal.makeTable
    let whiteLine = System.Console.ReadLine()
    let blackLine = System.Console.ReadLine()
    ColorDependent.processWhite whiteLine table
    ColorDependent.processBlack blackLine table
    Normal.showTable table
    0

[<EntryPoint>]
let main _ = realMain ()
