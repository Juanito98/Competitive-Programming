open Core

let mix a b = a lxor b
let prune a = a mod 16777216

let evolve number ~t =
  let step number =
    let number = number * 64 |> mix number |> prune in
    let number = number / 32 |> mix number |> prune in
    number * 2048 |> mix number |> prune
  in
  let[@tailrec] rec evolve number ~t ~acc =
    if t = 0 then number :: acc
    else evolve (step number) ~t:(t - 1) ~acc:(number :: acc)
  in
  evolve number ~t ~acc:[] |> List.rev

let part1 =
  List.sum
    (module Int)
    ~f:(fun secret_number -> evolve secret_number ~t:2000 |> List.last_exn)

let part2 secret_numbers =
  let module Sequence = struct
    type t = int * int * int * int [@@deriving sexp, compare, hash]
  end in
  let module SequenceMap = Map.Make (Sequence) in
  let sequences =
    List.map secret_numbers ~f:(fun secret_number ->
        let prices =
          evolve secret_number ~t:2000
          |> List.map ~f:(fun number -> number mod 10)
          |> List.to_array
        in
        let prices =
          Array.mapi prices ~f:(fun i curr ->
              let delta =
                if i = 0 then 0
                else
                  let prev = Array.get prices (i - 1) in
                  curr - prev
              in
              (curr, delta))
        in
        let sequences =
          Array.filter_mapi prices ~f:(fun i (price, _) ->
              if i < 4 then None
              else
                let sequence =
                  ( Array.get prices (i - 3) |> snd,
                    Array.get prices (i - 2) |> snd,
                    Array.get prices (i - 1) |> snd,
                    Array.get prices i |> snd )
                in
                Some (sequence, (i, price)))
          |> Array.to_list
          |> SequenceMap.of_alist_reduce ~f:(fun v1 v2 ->
                 if fst v1 < fst v2 then v1 else v2)
          |> SequenceMap.map ~f:snd
        in
        sequences)
  in
  List.fold sequences ~init:SequenceMap.empty ~f:(fun sequence_map acc ->
      Map.merge acc sequence_map ~f:(fun ~key:_ -> function
        | `Left v | `Right v -> Some v
        | `Both (v1, v2) -> Some (v1 + v2)))
  |> Map.to_alist
  |> List.max_elt ~compare:(fun (_seq1, v1) (_seq2, v2) -> Int.compare v1 v2)
  |> Option.value_exn |> snd

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let secret_numbers =
    String.split input ~on:'\n' |> List.map ~f:Int.of_string
  in
  let ans = solve part secret_numbers in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input = {|
1
2
3
2024
|} in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 37990510 |}];

  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 23 |}]

let%expect_test _ =
  let input = {|
1
10
100
2024
|} in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 37327623 |}];

  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 24 |}]
