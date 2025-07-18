open! Core

let invalid_input () = failwith "Invalid input"
let range_lenght (i, j) = j - i + 1

module Sublist = struct
  type t = { q : int Int.Hash_queue.t; mutable i : int; mutable j : int }

  let create () = { q = Int.Hash_queue.create (); i = 0; j = -1 }

  let enqueue t x =
    Hash_queue.enqueue_back_exn t.q x x;
    t.j <- t.j + 1

  let dequeue t =
    ignore (Hash_queue.dequeue_front_exn t.q);
    t.i <- t.i + 1

  let mem t x = Hash_queue.mem t.q x
  let range t = (t.i, t.j)
  let matches t criteria = range t |> criteria
end

(** Returns the max lenght subarray given some index (i, j) criteria *)
let sliding_window arr ~criteria =
  let acc = Sublist.create () in
  List.fold arr ~init:(0, 0) ~f:(fun best x ->
      while Sublist.mem acc x do
        Sublist.dequeue acc
      done;
      Sublist.enqueue acc x;
      let best =
        if
          Sublist.matches acc criteria
          && range_lenght (Sublist.range acc) > range_lenght best
        then Sublist.range acc
        else best
      in
      best)

let solve n arr =
  let i, j =
    sliding_window (arr @ arr) ~criteria:(fun (i, j) ->
        i = 0 || j = n - 1 || (i <= n && j >= n))
  in
  if i = 0 then (j + 1, n - 1)
  else if j = n - 1 then (0, i - 1)
  else ((j mod n) + 1, i - 1)

let main () =
  let input = In_channel.input_all Stdio.stdin in
  let lines = String.split_lines input in
  let _, n =
    match List.hd_exn lines |> String.split ~on:' ' with
    | t :: n :: _ -> (t, n) |> Tuple2.map ~f:Int.of_string
    | _ -> invalid_input ()
  in
  let arr =
    match lines with
    | _ :: arr :: _ -> String.split arr ~on:' ' |> List.map ~f:Int.of_string
    | _ -> invalid_input ()
  in
  let a, b = solve n arr in
  printf "%d %d\n" a b

let%expect_test _ =
  let input = {|
4 5
1 3 0 2 3
|} in
  Utils.For_tests.with_stdin input ~f:main;
  [%expect {| 4 4 |}]

let%expect_test _ =
  let input = {|
3 6
1 0 2 2 1 0  
|} in
  Utils.For_tests.with_stdin input ~f:main;
  [%expect {| 3 5 |}]

let%expect_test _ =
  let input = {|
4 8
0 2 0 1 2 1 3 3  
|} in
  Utils.For_tests.with_stdin input ~f:main;
  [%expect {| 2 6 |}]

let%expect_test _ =
  let input = {|
3 6
1 1 2 0 1 0  
|} in
  Utils.For_tests.with_stdin input ~f:main;
  [%expect {| 0 3 |}]

let%expect_test _ =
  let input = {|
5 13
3 3 3 1 2 0 3 3 2 1 4 1 0  
|} in
  Utils.For_tests.with_stdin input ~f:main;
  [%expect {| 1 9 |}]
