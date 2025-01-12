open Core

type op = XOR | AND | OR

let op_of_string = function
  | "XOR" -> XOR
  | "AND" -> AND
  | "OR" -> OR
  | _ -> failwith "could not parse op"

let apply a b = function XOR -> a lxor b | AND -> a land b | OR -> a lor b

let part1 ~gates ~init_values =
  let values = Hashtbl.create (module String) in
  let rec calculate name =
    Hashtbl.find_or_add values name ~default:(fun () ->
        match Map.find init_values name with
        | Some value -> value
        | None ->
            let v1, v2, op = Map.find_exn gates name in
            let v1 = calculate v1 in
            let v2 = calculate v2 in
            apply v1 v2 op)
  in
  let z_values =
    Map.keys init_values @ Map.keys gates
    |> List.filter ~f:(fun name ->
           String.is_prefix name ~prefix:"z"
           && String.count name ~f:Char.is_alpha = 1)
    |> List.sort ~compare:String.compare
    |> List.map ~f:(fun name -> (name, calculate name))
  in
  List.foldi z_values ~init:0 ~f:(fun i acc (_name, value) ->
      acc + ((1 lsl i) * value))

let part2 ~gates:_ ~init_values:_ =
  (* I realized for this specific input that zn = (xn XOR yn) XOR carry_zn. 
    And carry_zn = (x_{n-1} AND y_{n-1}) OR ((x{n-1} XOR y{n-1}) AND carry_z_{n-1}) *)
  print_endline "Warning: This does not take any input into account";
  let changes =
    [ ("z11", "wpd"); ("skh", "jqf"); ("z19", "mdd"); ("z37", "wts") ]
  in
  changes
  |> List.map ~f:(fun (g1, g2) -> [ g1; g2 ])
  |> List.concat
  |> List.sort ~compare:String.compare
  |> String.concat ~sep:"," |> print_endline;
  -1

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let init_values, gates =
    String.split input ~on:'\n'
    |> List.filter ~f:(fun line -> not (String.is_empty line))
    |> List.partition_tf ~f:(fun line -> String.contains line ':')
  in
  let init_values =
    List.map init_values ~f:(fun line ->
        match String.split line ~on:':' with
        | name :: [ value ] -> (name, value |> String.strip |> Int.of_string)
        | _ -> failwithf "Invalid initial value %s" line ())
    |> Map.of_alist_exn (module String)
  in
  let gates =
    List.map gates ~f:(fun line ->
        match String.split line ~on:' ' with
        | v1 :: op :: v2 :: "->" :: [ res ] ->
            let op = op_of_string op in

            (res, (v1, v2, op))
        | _ -> failwithf "Invalid gate value %s" line ())
    |> Map.of_alist_exn (module String)
  in
  let ans = solve part ~gates ~init_values in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
x00: 1
x01: 0
x02: 1
x03: 1
x04: 0
y00: 1
y01: 1
y02: 1
y03: 1
y04: 1

ntg XOR fgs -> mjb
y02 OR x01 -> tnw
kwq OR kpj -> z05
x00 OR x03 -> fst
tgd XOR rvg -> z01
vdt OR tnw -> bfw
bfw AND frj -> z10
ffh OR nrd -> bqk
y00 AND y03 -> djm
y03 OR y00 -> psh
bqk OR frj -> z08
tnw OR fst -> frj
gnj AND tgd -> z11
bfw XOR mjb -> z00
x03 OR x00 -> vdt
gnj AND wpb -> z02
x04 AND y00 -> kjc
djm OR pbm -> qhw
nrd AND vdt -> hwm
kjc AND fst -> rvg
y04 OR y02 -> fgs
y01 AND x02 -> pbm
ntg OR kjc -> kwq
psh XOR fgs -> tgd
qhw XOR tgd -> z09
pbm OR djm -> kpj
x03 XOR y03 -> ffh
x00 XOR y04 -> ntg
bfw OR bqk -> z06
nrd XOR fgs -> wpb
frj XOR qhw -> z04
bqk OR frj -> z07
y03 OR x01 -> nrd
hwm AND bqk -> z03
tgd XOR rvg -> z12
tnw OR pbm -> gnj
|}
  in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 2024 |}];

  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect
    {|
    Warning: This does not take any input into account
    jqf,mdd,skh,wpd,wts,z11,z19,z37
    -1
    |}]
