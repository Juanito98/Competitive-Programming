open Core

let pair_of_list = function
  | a :: [ b ] -> (a, b)
  | _ -> failwith "List is not a pair"

let find_interconnected adj =
  let connected_to_all u =
    List.for_all ~f:(fun w ->
        let adj_u = Map.find_exn adj u in
        Set.mem adj_u w)
  in
  let rec combinations = function
    | [] -> [ [] ]
    | x :: tail ->
        let don't_take = combinations tail in
        let take =
          List.filter_map don't_take ~f:(fun l ->
              if connected_to_all x l then Some (x :: l) else None)
        in
        don't_take @ take
  in
  let nodes = Map.keys adj in
  combinations nodes

let part1 adj =
  find_interconnected adj
  |> List.filter_map ~f:(function
       | a :: b :: [ c ] -> Some (a, b, c)
       | _ -> None)
  |> List.filter ~f:(fun (a, b, c) ->
         List.exists [ a; b; c ] ~f:(String.is_prefix ~prefix:"t"))
  |> List.length

let part2 adj =
  let ans =
    find_interconnected adj
    |> List.max_elt ~compare:(fun l1 l2 ->
           Int.compare (List.length l1) (List.length l2))
    |> Option.value_exn
  in
  print_endline (ans |> String.concat ~sep:",");
  ans |> List.length

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let adj =
    String.split input ~on:'\n'
    |> List.map ~f:(fun line -> String.split line ~on:'-' |> pair_of_list)
    |> List.fold
         ~init:(Map.empty (module String))
         ~f:(fun adj (u, v) ->
           Map.add_multi adj ~key:u ~data:v |> Map.add_multi ~key:v ~data:u)
    |> Map.map ~f:(Set.of_list (module String))
  in
  let ans = solve part adj in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
kh-tc
qp-kh
de-cg
ka-co
yn-aq
qp-ub
cg-tb
vc-aq
tb-ka
wh-tc
yn-cg
kh-ub
ta-co
de-co
tc-td
tb-wq
wh-td
ta-ka
td-qp
aq-cg
wq-ub
ub-vc
de-ta
wq-aq
wq-vc
wh-yn
ka-de
kh-ta
co-tc
wh-qp
tb-vc
td-yn
|}
  in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 7 |}];

  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {|
    co,de,ka,ta
    4
    |}]
