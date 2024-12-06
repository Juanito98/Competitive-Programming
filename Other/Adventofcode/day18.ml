open Core

module Pair = struct
  type t = int * int [@@deriving sexp, hash, compare]

  let sum (x, y) (v, w) = (x + v, y + w)
end

let pair_of_line line =
  match String.split line ~on:',' |> List.map ~f:Int.of_string with
  | [ i; j ] -> (i, j)
  | _ -> failwith "Invalid input"

let print mat ~n ~m =
  for i = 0 to n - 1 do
    for j = 0 to m - 1 do
      match Hashtbl.find mat (i, j) with
      | None -> print_string "."
      | Some -1 -> print_string "#"
      | Some x -> print_string (Int.to_string x)
    done;
    print_string "\n"
  done

let inside (i, j) ~n ~m = i >= 0 && j >= 0 && i < n && j < m

let part1_impl bytes ~n ~m ~t =
  let fallen = List.filteri bytes ~f:(fun i _ -> i < t) in
  let mat = Hashtbl.create (module Pair) in
  List.iter fallen ~f:(fun p -> Hashtbl.set mat ~key:p ~data:(-1));
  let q = Queue.create () in
  Queue.enqueue q ((0, 0), 0);
  while not (Queue.is_empty q) do
    let p, t = Queue.dequeue_exn q in
    if (not (inside p ~n ~m)) || Hashtbl.mem mat p then ()
    else (
      Hashtbl.set mat ~key:p ~data:t;
      List.iter
        [ (0, 1); (0, -1); (-1, 0); (1, 0) ]
        ~f:(fun d -> Queue.enqueue q (Pair.sum p d, t + 1)))
  done;
  Hashtbl.find mat (n - 1, m - 1)

let part1 bytes ~n ~m ~t =
  let ans = part1_impl bytes ~n ~m ~t |> Option.value_exn in
  print_s [%sexp (ans : int)]

let part2 bytes ~n ~m ~t:_ =
  let rec bin_search ~low ~high =
    if low = high then low
    else
      let med = (low + high + 1) / 2 in
      match part1_impl bytes ~n ~m ~t:med with
      | None -> bin_search ~low ~high:(med - 1)
      | Some _ -> bin_search ~low:med ~high
  in
  let t = bin_search ~low:0 ~high:(List.length bytes) in
  let _, (i, j) = List.findi_exn bytes ~f:(fun i _ -> i = t) in
  print_s [%sexp ((j, i) : int * int)]

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let (m, n), t, bytes =
    (* Swap the bytes to the conventional (row, column) notation *)
    match String.split input ~on:'\n' with
    | dimensions :: t :: bytes ->
        let dimensions = pair_of_line dimensions in
        let t = Int.of_string t in
        let bytes =
          List.map bytes ~f:pair_of_line |> List.map ~f:(fun (i, j) -> (j, i))
        in
        (dimensions, t, bytes)
    | _ -> failwith "Invalid input"
  in
  solve part bytes ~n ~m ~t

let%expect_test _ =
  let input =
    {|
7,7
12
5,4
4,2
4,5
3,0
2,1
6,3
2,4
1,5
0,6
3,3
2,6
5,1
1,2
5,5
2,5
6,5
1,4
0,4
6,4
1,1
6,1
1,0
0,5
1,6
2,0
|}
  in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 22 |}];
  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| (6 1) |}]
