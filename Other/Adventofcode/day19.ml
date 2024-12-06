open Core

module Id = struct
  let next_id = ref 0

  type t = int [@@deriving sexp, compare, hash]

  let create () =
    let id = !next_id in
    next_id := !next_id + 1;
    id
end

module Pair = struct
  type t = int * int [@@deriving sexp, compare, hash]
end

module Trie = struct
  module Node = struct
    type t = {
      id : Id.t;
      v : char;
      children : t Hashtbl.M(Char).t;
      mutable is_final : bool;
    }
    [@@deriving sexp_of]

    let create v =
      {
        id = Id.create ();
        v;
        children = Hashtbl.create (module Char);
        is_final = false;
      }

    let set_is_final t = t.is_final <- true
  end

  let create () = Node.create '$'

  let insert ~root s =
    let leaf =
      String.fold s ~init:root ~f:(fun node c ->
          Hashtbl.find_or_add node.Node.children c ~default:(fun () ->
              Node.create c))
    in
    Node.set_is_final leaf

  let count_cover ~root s =
    let memo = Hashtbl.create (module Pair) in
    let rec count_cover node i =
      if i >= String.length s then if node.Node.is_final then 1 else 0
      else
        match Hashtbl.find memo (node.Node.id, i) with
        | Some ans -> ans
        | None ->
            let c = String.get s i in
            let continue =
              match Hashtbl.find node.children c with
              | Some child -> count_cover child (i + 1)
              | None -> 0
            in
            let cut = if node.is_final then count_cover root i else 0 in
            let ans = continue + cut in
            Hashtbl.set memo ~key:(node.id, i) ~data:ans;
            ans
    in
    count_cover root 0
end

let part1 ~patterns ~towels =
  let root = Trie.create () in
  List.iter patterns ~f:(Trie.insert ~root);
  List.fold towels ~init:0 ~f:(fun acc towel ->
      if Trie.count_cover ~root towel > 0 then acc + 1 else acc)

let part2 ~patterns ~towels =
  let root = Trie.create () in
  List.iter patterns ~f:(Trie.insert ~root);
  List.fold towels ~init:0 ~f:(fun acc towel ->
      acc + Trie.count_cover ~root towel)

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let patterns, towels =
    match String.split input ~on:'\n' with
    | patterns :: "" :: towels ->
        let patterns =
          String.split patterns ~on:',' |> List.map ~f:String.strip
        in
        (patterns, towels)
    | _ -> failwith "Invalid input"
  in
  let ans = solve part ~patterns ~towels in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
r, wr, b, g, bwu, rb, gb, br

brwrr
bggr
gbbr
rrbgbr
ubwu
bwurrg
brgr
bbrgwb
|}
  in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 6 |}];
  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 16 |}]
