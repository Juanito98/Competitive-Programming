open Core

let numeric_keypad_pos =
  List.init 9 ~f:(fun num ->
      let c = Int.to_string (num + 1) |> Char.of_string in
      let i = 2 - (num / 3) in
      let j = num % 3 in
      (c, (i, j)))
  @ [ ('0', (3, 1)); ('A', (3, 2)) ]
  |> Map.of_alist_exn (module Char)

let directional_keypad_pos =
  [ ('^', (0, 1)); ('A', (0, 2)); ('<', (1, 0)); ('v', (1, 1)); ('>', (1, 2)) ]
  |> Map.of_alist_exn (module Char)

type whom = Numeric_robot | Directional_robot of int
[@@deriving sexp, compare, equal, hash]

(** The min sequence to move the robot [whom] if it is in [from_] and wants to
    press [to_] *)
let min_step ~from_ ~to_ ~whom =
  let keypad_pos, gap =
    match whom with
    | Numeric_robot -> (numeric_keypad_pos, (3, 0))
    | Directional_robot _ -> (directional_keypad_pos, (0, 0))
  in
  let ui, uj = Map.find_exn keypad_pos from_ in
  let wi, wj = Map.find_exn keypad_pos to_ in
  let vert =
    String.init (abs (ui - wi)) ~f:(fun _ -> if ui < wi then 'v' else '^')
  in
  let hori =
    String.init (abs (uj - wj)) ~f:(fun _ -> if uj < wj then '>' else '<')
  in
  let vert_hori =
    if [%equal: int * int] (wi, uj) gap then None else Some (vert ^ hori ^ "A")
  in
  let hori_vert =
    if [%equal: int * int] (ui, wj) gap then None else Some (hori ^ vert ^ "A")
  in
  List.filter_opt [ vert_hori; hori_vert ]
  |> List.dedup_and_sort ~compare:String.compare

let shortest_sequence code ~last =
  let module Key = struct
    type t = { from_ : char; to_ : char; whom : whom }
    [@@deriving sexp, compare, hash]
  end in
  let memo = Hashtbl.create (module Key) in
  let rec shortest_sequence_path ~from_ ~to_ ~whom =
    Hashtbl.find_or_add memo { Key.from_; to_; whom } ~default:(fun () ->
        min_step ~from_ ~to_ ~whom
        |> List.map ~f:(fun code ->
               if equal_whom whom last then String.length code
               else
                 let next_ =
                   match whom with
                   | Numeric_robot -> Directional_robot 1
                   | Directional_robot i -> Directional_robot (i + 1)
                 in
                 shortest_sequence code ~whom:next_)
        |> List.min_elt ~compare:Int.compare
        |> Option.value_exn)
  and shortest_sequence code ~whom =
    String.to_list code
    |> List.mapi ~f:(fun i to_ ->
           let from_ = if i > 0 then String.get code (i - 1) else 'A' in
           shortest_sequence_path ~from_ ~to_ ~whom)
    |> List.sum (module Int) ~f:Fn.id
  in
  shortest_sequence code ~whom:Numeric_robot

let numeric_part code = String.filter code ~f:Char.is_digit |> Int.of_string

let complexity codes ~last =
  List.map codes ~f:(fun code ->
      let shortest_sequence = shortest_sequence code ~last in
      let numeric_part = numeric_part code in
      shortest_sequence * numeric_part)
  |> List.sum (module Int) ~f:Fn.id

let part1 = complexity ~last:(Directional_robot 2)
let part2 = complexity ~last:(Directional_robot 25)
let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let codes = String.split input ~on:'\n' in
  let ans = solve part codes in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input = {|
029A
980A
179A
456A
379A
|} in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 126384 |}];

  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 154115708116294 |}]

let%expect_test _ =
  let input = {|
935A
319A
480A
789A
176A
|} in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 188398 |}];

  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 230049027535970 |}]
