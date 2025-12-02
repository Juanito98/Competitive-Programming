open Core
open Composition_infix

let area_matrix (px, py) (qx, qy) = (abs (px - qx) + 1) * (abs (py - qy) + 1)

let part1 arr =
  List.fold arr ~init:0 ~f:(fun max_area p ->
      List.fold arr ~init:max_area ~f:(fun max_area q ->
          max max_area (area_matrix p q)))

(** Returns the normalized rectangle. *)
let intersect_rectangles r1 r2 =
  let normalized_rectangle_vertex ((px, py), (qx, qy)) =
    ((min px qx, min py qy), (max px qx, max py qy))
  in
  let (px, py), (qx, qy) = normalized_rectangle_vertex r1 in
  let (ux, uy), (wx, wy) = normalized_rectangle_vertex r2 in
  let ans_px, ans_py = (max px ux, max py uy) in
  let ans_qx, ans_qy = (min qx wx, min qy wy) in
  if ans_px > ans_qx || ans_py > ans_qy then None
  else Some ((ans_px, ans_py), (ans_qx, ans_qy))

(** The area in the plane, not in a matrix. Difference is that the lines does
    not have area. *)
let area (px, py) (qx, qy) = abs (px - qx) * abs (py - qy)

let part2 arr =
  let lines =
    let shifted =
      match arr with hd :: tl -> tl @ [ hd ] | _ -> assert false
    in
    List.zip_exn arr shifted
  in
  let horizontal =
    List.filter_map lines ~f:(fun ((px, py), (qx, qy)) ->
        if py = qy then Some ((px, qx), py) else None)
  in
  let intersection_area p q =
    List.sum
      (module Int)
      horizontal
      ~f:(fun ((x1, x2), y) ->
        let sign = if x1 < x2 then 1 else -1 in
        let intersected_rectangle =
          intersect_rectangles (p, q) ((x1, 0), (x2, y))
        in
        let intersected_area =
          Option.value_map intersected_rectangle ~default:0 ~f:(fun (p, q) ->
              area p q)
        in
        sign * intersected_area)
    |> abs
  in
  let should_consider p q = intersection_area p q = area p q in
  List.fold arr ~init:0 ~f:(fun max_area p ->
      List.fold arr ~init:max_area ~f:(fun max_area q ->
          if should_consider p q then max max_area (area_matrix p q)
          else max_area))

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let arr =
    String.split_lines input
    |> List.map
         ~f:
           ( String.split ~on:',' >> function
             | a :: b :: _ -> (a, b) |> Tuple2.map ~f:Int.of_string
             | _ -> assert false )
  in
  let ans = solve part arr in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input = {|
7,1
11,1
11,7
9,7
9,5
2,5
2,3
7,3
|} in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 50 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 24 |}]
