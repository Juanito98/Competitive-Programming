open Core
open Composition_infix

let indicator_to_int indicator =
  String.foldi indicator ~init:0 ~f:(fun i acc -> function
    | '#' -> acc + (1 lsl i)
    | _ -> acc)

let apply_button button indicator =
  List.fold button ~init:indicator ~f:(fun indicator button ->
      indicator lxor (1 lsl button))

let part1 arr =
  let f (indicator, buttons) =
    let all = List.init (1 lsl String.length indicator) ~f:Fn.id in
    let dp =
      List.fold buttons
        ~init:(Map.singleton (module Int) 0 0)
        ~f:(fun dp button ->
          List.fold all ~init:dp ~f:(fun dp indicator ->
              match Map.find dp (apply_button button indicator) with
              | None -> dp
              | Some c ->
                  let c = c + 1 in
                  let data =
                    match Map.find dp indicator with
                    | None -> c
                    | Some c' -> min c c'
                  in
                  Map.set dp ~key:indicator ~data))
    in
    Map.find dp (indicator_to_int indicator) |> Option.value_exn
  in
  List.sum
    (module Int)
    arr
    ~f:(fun (indicator, buttons, _) -> f (indicator, buttons))

let apply_button button joltage ~n =
  let new_joltage =
    List.folding_mapi joltage ~init:button ~f:(fun i button joltage ->
        let new_button = List.drop_while button ~f:(fun j -> j < i) in
        let new_joltage =
          match List.hd new_button with
          | Some j when j = i -> joltage - n
          | Some _ | None -> joltage
        in
        (new_button, new_joltage))
  in
  Option.some_if (List.for_all new_joltage ~f:(fun x -> x >= 0)) new_joltage

let%expect_test _ =
  let test ?(n = 1) button joltage =
    let new_joltage = apply_button button joltage ~n in
    print_s [%sexp (new_joltage : int list option)]
  in
  test [ 1; 3 ] [ 44; 35; 48; 43; 24; 44 ];
  [%expect {| ((44 34 48 42 24 44)) |}];
  test [ 1; 3 ] [ 44; 35; 48; 43; 24; 44 ] ~n:5;
  [%expect {| ((44 30 48 38 24 44)) |}];
  test [ 1; 3 ] [ 44; 35; 48; 43; 24; 44 ] ~n:50;
  [%expect {| () |}]

let part2 arr =
  let sort_list_by_first_element =
    List.sort ~compare:(fun l1 l2 ->
        Int.compare (List.hd_exn l1) (List.hd_exn l2))
  in
  let rec f (buttons, joltage) =
    match joltage with
    | [] -> Some 0
    | 0 :: new_joltage ->
        let new_buttons =
          (* Buttons that don't affect 0. *)
          List.filter_map buttons ~f:(function
            | [] | 0 :: _ -> None
            | other -> Some (List.map other ~f:(fun x -> x - 1)))
        in
        f (sort_list_by_first_element new_buttons, new_joltage)
    | hd :: _ -> (
        match buttons with
        | (0 :: _ as button) :: new_buttons ->
            let options =
              match new_buttons with
              | (0 :: _) :: _ -> List.init (hd + 1) ~f:Fn.id
              | _ -> [ hd ]
            in
            List.fold_until options ~init:None ~finish:Fn.id ~f:(fun acc n ->
                match apply_button button joltage ~n with
                | None -> Stop acc
                | Some new_joltage ->
                    let cost =
                      let%map.Option cost = f (new_buttons, new_joltage) in
                      cost + n
                    in
                    let best =
                      match (acc, cost) with
                      | None, None -> None
                      | None, x | x, None -> x
                      | Some x, Some y -> Some (min x y)
                    in
                    Continue best)
        | [] | _ :: _ -> None (* There are no buttons to configure head. *))
  in

  List.sum
    (module Int)
    arr
    ~f:(fun (_, buttons, joltage) ->
      f (sort_list_by_first_element buttons, joltage) |> Option.value_exn)

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let arr =
    String.split_lines input
    |> List.map ~f:(fun line ->
           let line = String.split line ~on:' ' in
           let take_first = function
             | hd :: tl -> (hd, tl)
             | _ -> assert false
           in
           let indicator, rest = take_first line in
           let joltage, buttons = List.rev rest |> take_first in
           let indicator =
             indicator
             |> String.chop_prefix_exn ~prefix:"["
             |> String.chop_suffix_exn ~suffix:"]"
           in
           let buttons =
             List.map buttons
               ~f:
                 (String.chop_prefix_exn ~prefix:"("
                 >> String.chop_suffix_exn ~suffix:")"
                 >> String.split ~on:',' >> List.map ~f:Int.of_string
                 >> List.sort ~compare:Int.compare)
           in
           let joltage =
             String.chop_prefix_exn joltage ~prefix:"{"
             |> String.chop_suffix_exn ~suffix:"}"
             |> String.split ~on:',' |> List.map ~f:Int.of_string
           in
           (indicator, buttons, joltage))
  in
  let ans = solve part arr in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 7 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 33 |}]
