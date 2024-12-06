open Core

let part1 equations =
  let valid eq msc =
    let sum =
      let init, nums =
        match snd eq with
        | init :: nums -> (init, nums)
        | _ -> failwith "Invalid equation"
      in
      List.foldi nums ~init ~f:(fun idx acc num ->
          let bi = msc land (1 lsl idx) in
          if bi > 0 then acc + num else acc * num)
    in
    sum = fst eq
  in
  List.filter equations ~f:(fun eq ->
      let msc =
        List.init (1 lsl List.length (snd eq)) ~f:Fun.id
        |> List.find ~f:(valid eq)
      in
      Option.is_some msc)

let rec pow n exp =
  if exp = 0 then 1
  else
    let x = pow n (exp / 2) in
    let x = x * x in
    if exp land 1 = 1 then x * n else x

let part2 equations =
  let valid eq msc =
    let sum =
      let init, nums =
        match snd eq with
        | init :: nums -> (init, nums)
        | _ -> failwith "Invalid equation"
      in
      let msc = ref msc in
      List.fold nums ~init ~f:(fun acc num ->
          let bi = !msc % 3 in
          msc := !msc / 3;
          if bi = 0 then acc + num
          else if bi = 1 then acc * num
          else Int.to_string acc ^ Int.to_string num |> Int.of_string)
    in
    sum = fst eq
  in
  List.filter equations ~f:(fun eq ->
      let msc =
        List.init (pow 3 (List.length (snd eq))) ~f:Fun.id
        |> List.find ~f:(valid eq)
      in
      Option.is_some msc)

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let equations =
    String.split input ~on:'\n'
    |> List.map ~f:(fun line ->
           match String.split line ~on:':' with
           | a :: [ nums ] ->
               let a = Int.of_string a in
               let nums =
                 String.strip nums |> String.split ~on:' '
                 |> List.map ~f:Int.of_string
               in
               (a, nums)
           | _ -> failwith "Invalid line")
  in
  let ans =
    solve part equations |> List.map ~f:fst |> List.fold ~init:0 ~f:( + )
  in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 3749 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 11387 |}]
