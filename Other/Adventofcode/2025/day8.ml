open Core
open Composition_infix

let square x = x * x

let dist2 (px, py, pz) (qx, qy, qz) =
  square (px - qx) + square (py - qy) + square (pz - qz)

let compute_adj points =
  List.concat_mapi points ~f:(fun u p ->
      List.mapi points ~f:(fun v q -> (u, v, dist2 p q)))
  |> List.sort ~compare:[%compare: _ * _ * int]
  |> List.filter ~f:(fun (u, v, _) -> u < v)

let rec root node parents =
  let parent = Map.find parents node |> Option.value ~default:node in
  if parent = node then (node, parents)
  else
    let ans, parents = root parent parents in
    (ans, Map.set parents ~key:node ~data:ans)

let part1 (points : (int * int * int) list) ~num_connections =
  let n = List.length points in
  let adj = compute_adj points in
  let parents =
    List.foldi adj
      ~init:(Map.empty (module Int))
      ~f:(fun edge_num parents (u, v, _d) ->
        if edge_num >= num_connections then parents
        else
          let root_u, parents = root u parents in
          let root_v, parents = root v parents in
          if root_u = root_v then parents
          else Map.set parents ~key:root_u ~data:root_v)
  in
  let roots =
    List.init n ~f:(fun node -> (root node parents |> fst, node))
    |> Map.of_alist_multi (module Int)
  in
  Map.data roots |> List.map ~f:List.length
  |> List.sort ~compare:Int.compare
  |> List.rev
  |> function
  | a :: b :: c :: _ -> a * b * c
  | _ -> assert false

let part2 points =
  let n = List.length points in
  let adj = compute_adj points in
  let (px, _, _), (qx, _, _) =
    List.fold_until adj
      ~init:(0, Map.empty (module Int))
      ~f:(fun (edge_num, parents) (u, v, _d) ->
        let edge_num, parents =
          let root_u, parents = root u parents in
          let root_v, parents = root v parents in
          if root_u = root_v then (edge_num, parents)
          else (edge_num + 1, Map.set parents ~key:root_u ~data:root_v)
        in
        if edge_num = n - 1 then
          Continue_or_stop.Stop (List.nth_exn points u, List.nth_exn points v)
        else Continue (edge_num, parents))
      ~finish:(fun _ -> assert false)
  in
  px * qx

let solve ~num_connections = function
  | `Part_1 -> part1 ~num_connections
  | `Part_2 -> part2

let main ?(num_connections = 1000) () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let points =
    String.split_lines input
    |> List.map
         ~f:
           ( String.split ~on:',' >> List.map ~f:Int.of_string >> function
             | a :: b :: c :: _ -> (a, b, c)
             | _ -> assert false )
  in
  let ans = solve part points ~num_connections in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
162,817,812
57,618,57
906,360,560
592,479,940
352,342,300
466,668,158
542,29,236
431,825,988
739,650,466
52,470,668
216,146,977
819,987,18
117,168,530
805,96,715
346,949,466
970,615,88
941,993,340
862,61,35
984,92,344
425,690,689
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~num_connections:10 ~part:`Part_1);
  [%expect {| 40 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 25272 |}]
