import math

def forming_force_spif(r, to, h, alpha_degree, yield_stress, k, n):
    alpha = alpha_degree * math.pi / 180
    t = to * math.cos(alpha)  # t = actual sheet thickness
    numerator = t * (1 - math.cos(alpha))
    denomenator = alpha * (3 - (math.pi / 2)) + 1
    h1_ = numerator / denomenator  # h1_ = Sheet thickness thinning at the bottom of the sheet
    h1__ = math.sqrt(2 * h * t / r)  # h1__ = Elastic deflection of sheet in vertical direction
    h1 = h1_ + h1__  # h1 = pressed amount of the forming tool
    slack1 = r**2 - ((h / (2 * math.sin(alpha)))**2)
    hs = r - math.sqrt(slack1)  # hs = Scallop height on the sheet surface
    l1 = r * math.acos((r - h1) / r)
    l2 = r * alpha
    l3 = r * math.acos((r - hs) / r)
    slack2 = (r * (l2 + l3) * (1 - math.cos(alpha))) / l1
    S = (math.pi * r * (h1 + slack2)) / 2  # S = Surface area of ellipsoidal crown
    equi_strain = (2 / math.sqrt(3)) * math.log((2 * r) / ((2 * r * math.cos(alpha)) + (t * math.cos(alpha))))
    equi_stress = yield_stress + (k * (1 - math.exp((-n) * equi_strain)))
    thickness_stress = (4 * t * equi_stress) / (math.sqrt(3) * (r + 2.5 * t))
    force_spif = thickness_stress * S  # Force_SPIF = Analytical resultant force of SPIF
    return force_spif

def forming_force_ihf(r, to, h, alpha_degree, yield_stress, k, n):
    force_ihf = forming_force_spif(r, to, h, alpha_degree, yield_stress, k, n)
    if not math.isnan(force_ihf):
        return force_ihf / 2
    else:
        return force_ihf

while True:
    print("\n Select a option from the below list to proceed:")
    print(" 1.To calculate forming force of spif(Single Pass Incremental Forming)")
    print(" 2.To calculate forming force of ihf(Incremental Hole Flanging)")
    print(" 3.To exit from the program")
    option = int(input())
    if option > 3:
        print("\n Invalid option. Program terminates!")
    if option > 2:
        break
    r = float(input("\n Enter tool radius(r) in meter: "))
    to = float(input("\n Enter initial sheet thickness(to) in meter: "))
    h = float(input("\n Enter step depth of the tool(h) in meter: "))
    alpha_degree = float(input("\n Enter wall angle of part(alpha) in degree: "))
    yield_stress = float(input("\n Enter yield stress of workpiece material in MPa: "))
    k = float(input("\n Enter the value of constant 'K' to calculate equivalent stress: "))
    n = float(input("\n Enter the value of constant 'n' to calculate equivalent stress: "))
    while True:
            if option == 1:
                force_spif = forming_force_spif(r, to, h, alpha_degree, yield_stress, k, n)
                if math.isnan(force_spif):
                    print("\n Some of the input values entered are not logically correct with the assumptions taken in this model!!")
                else:
                    print("\n Analytical resultant forming force of SPIF is:", force_spif, "MN")
                break

            elif option == 2:
                force_ihf = forming_force_ihf(r, to, h, alpha_degree, yield_stress, k, n)
                if math.isnan(force_ihf):
                    print("\n Some of the input values entered are not logically correct with the assumptions taken in this model!!")
                else:
                    print("\n Analytical resultant forming force of ihf is:", force_ihf, "MN")
                break

            else:
                print("\n Invalid option. Program terminates!")
                break
        
    s = input("\n Do you want to calculate other forces using same input(Y/N): ")
    if(s == 'Y' or s == 'y'):
        print("\n Select a option from the below list to proceed: ")
        print(" 1.To calculate forming force of spif(Single Pass Incremental Forming)")
        print(" 2.To calculate forming force of ihf(Incremental Hole Flanging)")
        print(" 3.To exit from the program")
        option = int(input())

        if(option > 3):
            print("\n Invalid option. Program terminates!")
        if(option > 2):
            break

        continue

    choice = input("\n Do you want to calculate other forces using different input(Y/N): ")
    if(choice == 'N' or choice == 'n'):
        break

