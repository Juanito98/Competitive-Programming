open Core

let has_no_children adj node =
  Map.find adj node |> Option.value_map ~default:true ~f:Set.is_empty

let count_paths ~from_node ~to_node adj =
  let rev_adj =
    Map.fold adj ~init:String.Map.empty ~f:(fun ~key:node ~data acc ->
        Set.fold data ~init:acc ~f:(fun acc child ->
            let child_adj =
              Map.find acc child |> Option.value ~default:String.Set.empty
            in
            let child_adj = Set.add child_adj node in
            Map.set acc ~key:child ~data:child_adj))
  in
  let rec bfs ans queue ~adj ~rev_adj =
    match queue with
    | [] -> ans
    | hd :: tl ->
        if has_no_children adj hd then
          let hd_rev_adj =
            Map.find rev_adj hd |> Option.value_map ~f:Set.to_list ~default:[]
          in
          let new_ans =
            let hd_ways = Map.find ans hd |> Option.value ~default:0 in
            List.fold hd_rev_adj ~init:ans ~f:(fun ans parent ->
                let parent_ans =
                  Map.find ans parent |> Option.value ~default:0
                in
                Map.set ans ~key:parent ~data:(parent_ans + hd_ways))
          in
          let new_adj =
            List.fold hd_rev_adj ~init:adj ~f:(fun adj parent ->
                let parent_adj = Map.find_exn adj parent in
                Map.set adj ~key:parent ~data:(Set.remove parent_adj hd))
          in
          let new_rev_adj = Map.set rev_adj ~key:hd ~data:String.Set.empty in
          (bfs [@tailcall]) new_ans (tl @ hd_rev_adj) ~adj:new_adj
            ~rev_adj:new_rev_adj
        else (bfs [@tailcall]) ans tl ~adj ~rev_adj
  in
  let initial_queue =
    let all_nodes = Set.union (Map.key_set adj) (Map.key_set rev_adj) in
    Set.filter all_nodes ~f:(has_no_children adj) |> Set.to_list
  in
  let ans = bfs (String.Map.singleton to_node 1) initial_queue ~adj ~rev_adj in
  Map.find ans from_node |> Option.value ~default:0

let part1 = count_paths ~from_node:"you" ~to_node:"out"

let remove_node adj node =
  Map.remove adj node |> Map.map ~f:(fun s -> Set.remove s node)

let part2 adj =
  let count_paths = count_paths ~from_node:"svr" ~to_node:"out" in
  let dac = "dac" in
  let fft = "fft" in
  let all = count_paths adj in
  let without_dac = count_paths (remove_node adj dac) in
  let without_fft = count_paths (remove_node adj fft) in
  let without_any = count_paths (remove_node (remove_node adj dac) fft) in
  all - without_dac + (all - without_fft) - (all - without_any)

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let adj =
    String.split_lines input
    |> List.map ~f:(fun line ->
           match String.split line ~on:' ' with
           | node :: children ->
               ( String.chop_suffix_exn ~suffix:":" node,
                 String.Set.of_list children )
           | _ -> assert false)
    |> String.Map.of_alist_exn
  in
  let ans = solve part adj in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
aaa: you hhh
you: bbb ccc
bbb: ddd eee
ccc: ddd eee fff
ddd: ggg
eee: out
fff: out
ggg: out
hhh: ccc fff iii
iii: out
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 5 |}];
  let input =
    {|
svr: aaa bbb
aaa: fft
fft: ccc
bbb: tty
tty: ccc
ccc: ddd eee
ddd: hub
hub: fff
eee: dac
dac: fff
fff: ggg hhh
ggg: out
hhh: out
|}
  in
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 2 |}]
