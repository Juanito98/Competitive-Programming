open Core

module Pair = struct
  type t = int * int [@@deriving sexp, compare, hash]
end

let rec blink stone ~t ~memo =
  if t <= 0 then 1
  else
    match Hashtbl.find memo (stone, t) with
    | None ->
        let ans =
          if stone = 0 then blink 1 ~t:(t - 1) ~memo
          else
            let num = Int.to_string stone in
            let len = String.length num in
            if len land 1 = 0 then
              let left =
                String.sub num ~pos:0 ~len:(len / 2) |> Int.of_string
              in
              let right =
                String.sub num ~pos:(len / 2) ~len:(len / 2) |> Int.of_string
              in
              blink left ~t:(t - 1) ~memo + blink right ~t:(t - 1) ~memo
            else blink (stone * 2024) ~t:(t - 1) ~memo
        in
        Hashtbl.set memo ~key:(stone, t) ~data:ans;
        ans
    | Some ans -> ans

let solve stones ~t =
  List.map stones ~f:(blink ~t ~memo:(Hashtbl.create (module Pair)))
  |> List.sum (module Int) ~f:Fn.id

let main () =
  let input = In_channel.input_all Stdio.stdin in
  let stones, t =
    match String.split input ~on:'\n' with
    | stones :: [ t ] ->
        ( stones |> String.split ~on:' ' |> List.map ~f:Int.of_string,
          Int.of_string t )
    | _ -> failwithf "Invalid input %s" input ()
  in
  let ans = solve ~t stones in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input = {|7725 185 2 132869 0 1840437 62 26310|} in
  (* Part 1*)
  Utils.For_tests.with_stdin [%string {|
%{input}
25
|}] ~f:main;
  [%expect {| 233050 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin [%string {|
%{input}
75
|}] ~f:main;
  [%expect {| 276661131175807 |}]
