open Core
open Composition_infix

let compute = function
  | [] -> assert false
  | hd :: tl ->
      let init = List.map hd ~f:(function 'S' -> ('S', 1) | x -> (x, 0)) in
      init
      :: List.folding_map tl ~init ~f:(fun prev line ->
             let new_line =
               (* Check if above is '|' or 'S' *)
               List.zip_exn prev line
               |> List.map ~f:(function
                    | (('|' | 'S'), cnt), '.' -> ('|', cnt)
                    | (('|' | 'S'), cnt), '^' -> ('x', cnt)
                    | _, curr -> (curr, 0))
             in
             let folding_map =
               (* Check if left is 'x' *)
               function
               | [] -> assert false
               | init :: tl ->
                   init
                   :: List.folding_map tl ~init
                        ~f:(fun (prev, prev_cnt) (curr, curr_cnt) ->
                          let new_ =
                            match (prev, curr) with
                            | 'x', ('.' | '|') -> ('|', curr_cnt + prev_cnt)
                            | _, curr -> (curr, curr_cnt)
                          in
                          (new_, new_))
             in
             let new_line = folding_map new_line in
             let new_line = List.rev new_line |> folding_map |> List.rev in
             (new_line, new_line))

let part1 (mat : char list list) =
  let mat = compute mat in
  List.sum
    (module Int)
    mat
    ~f:(List.map ~f:fst >> List.count ~f:([%compare.equal: char] 'x'))

let part2 mat =
  let mat = compute mat in
  List.last_exn mat |> List.map ~f:snd |> List.sum (module Int) ~f:Fn.id

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let mat = String.split_lines input |> List.map ~f:String.to_list in
  let ans = solve part mat in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
.......S.......
...............
.......^.......
...............
......^.^......
...............
.....^.^.^.....
...............
....^.^...^....
...............
...^.^...^.^...
...............
..^...^.....^..
...............
.^.^.^.^.^...^.
...............
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 21 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 40 |}]
